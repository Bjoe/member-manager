#include "dao/memberdao.h"
#include "dao/databasestructure.h"

namespace membermanager
{
namespace dao
{

MemberDao::MemberDao(const QSqlDatabase &aDatabase, QObject *aParent) :
    database(aDatabase),
    memberModel(new QSqlTableModel(aParent, aDatabase)),
    ressourcenModel(new QSqlTableModel(aParent, aDatabase)),
    bankModel(new QSqlTableModel(aParent, aDatabase)),
    addressModel(new QSqlTableModel(aParent, aDatabase))
{
    memberModel->setTable(dao::MemberTable::TABLENAME);
    memberModel->setObjectName(dao::MemberTable::TABLENAME);
    memberModel->setHeaderData(MemberTable::MemberId, Qt::Horizontal, memberModel->tr("Nr."));
    memberModel->setHeaderData(MemberTable::FirstName, Qt::Horizontal, memberModel->tr("Vorname"));
    memberModel->setHeaderData(MemberTable::Name, Qt::Horizontal, memberModel->tr("Name"));
    memberModel->setHeaderData(MemberTable::NickName, Qt::Horizontal, memberModel->tr("Nickname"));
    memberModel->setHeaderData(MemberTable::EntryDate, Qt::Horizontal, memberModel->tr("Eintritts Datum"));
    memberModel->select();

    ressourcenModel->setTable(dao::RessourcenTable::TABLENAME);
    ressourcenModel->setObjectName(dao::RessourcenTable::TABLENAME);

    bankModel->setTable(dao::BankAccountTable::TABLENAME);
    bankModel->setObjectName(dao::BankAccountTable::TABLENAME);

    addressModel->setTable(dao::AddressTable::TABLENAME);
    addressModel->setObjectName(dao::AddressTable::TABLENAME);
}

bool MemberDao::saveRecord(const Member &aMember)
{
    int memberId = aMember.getMemberId();
    bool successful = true;

    QSqlRecord record = aMember.memberRecord;
    QString columnId = dao::MemberTable::COLUMNNAME[dao::MemberTable::MemberId];
    selectTableModel(memberModel, columnId, memberId);
    successful &= saveRecordOnModel(memberModel, record);

    selectTableModel(ressourcenModel, dao::RessourcenTable::COLUMNNAME[dao::RessourcenTable::MemberId], memberId);
    record = aMember.ressourcenRecord;
    successful &= saveRecordOnModel(ressourcenModel, record);

    selectTableModel(bankModel, dao::BankAccountTable::COLUMNNAME[dao::BankAccountTable::MemberId], memberId);
    record = aMember.bankRecord;
    successful &= saveRecordOnModel(bankModel, record);

    selectTableModel(addressModel, dao::AddressTable::COLUMNNAME[dao::AddressTable::MemberId], memberId);
    record = aMember.addressRecord;
    successful &= saveRecordOnModel(addressModel, record);

    return successful;
}

Member MemberDao::findByMemberId(int aMemberId)
{
    Member member;

    selectTableModel(addressModel, dao::AddressTable::COLUMNNAME[dao::AddressTable::MemberId], aMemberId);
    member.addressRecord = record(addressModel);

    selectTableModel(bankModel, dao::BankAccountTable::COLUMNNAME[dao::BankAccountTable::MemberId], aMemberId);
    member.bankRecord = record(bankModel);

    selectTableModel(ressourcenModel, dao::RessourcenTable::COLUMNNAME[dao::RessourcenTable::MemberId], aMemberId);
    member.ressourcenRecord = record(ressourcenModel);

    selectTableModel(memberModel, dao::MemberTable::COLUMNNAME[dao::MemberTable::MemberId], aMemberId);
    member.memberRecord = record(memberModel);

    return member;
}

Member MemberDao::findByRow(int aRowNr)
{
    Member member;

    member.memberRecord = memberModel->record(aRowNr);

    int memberId = member.getMemberId();
    selectTableModel(bankModel, dao::BankAccountTable::COLUMNNAME[dao::BankAccountTable::MemberId], memberId);
    member.bankRecord = record(bankModel);

    selectTableModel(ressourcenModel, dao::RessourcenTable::COLUMNNAME[dao::RessourcenTable::MemberId], memberId);
    member.ressourcenRecord = record(ressourcenModel);

    return member;
}

QSqlTableModel *MemberDao::selectDeleted(bool isDeleted)
{
    QString deleted = "'false'";
    if(isDeleted) {
        deleted = "'true'";
    }

    QString columnname = dao::MemberTable::COLUMNNAME[dao::MemberTable::Deleted];
    QString filter = QString("%1 = %2").arg(columnname).arg(deleted);

    memberModel->setFilter(filter);
    memberModel->select();

    return memberModel;
}

QList<Member> MemberDao::findByDeleted(bool isDeleted)
{
    selectDeleted(isDeleted);

    QList<Member> list;
    for(int row = 0; row < memberModel->rowCount(); row++) {
        QModelIndex index = memberModel->index(row, dao::MemberTable::MemberId);
        QVariant variant = index.data();
        Member member = findByMemberId(variant.toInt());
        list.append(member);
    }
    return list;
}

QSqlTableModel *MemberDao::model()
{
    return memberModel;
}

/// \todo createMember()
int MemberDao::newMember()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QDate date = dateTime.date();
    QString firstname = QString("new%1").arg(dateTime.toMSecsSinceEpoch());
    database.transaction();
    QSqlQuery query(database);

    query.prepare("INSERT INTO " + MemberTable::TABLENAME +
                  " (" + MemberTable::COLUMNNAME[MemberTable::Deleted] +
                  " ," + MemberTable::COLUMNNAME[MemberTable::EntryDate] +
                  " ," + MemberTable::COLUMNNAME[MemberTable::FirstName] +
                  ") VALUES (? ,? ,? )");
    query.addBindValue("true");
    query.addBindValue(date.toString(Qt::ISODate));
    query.addBindValue(firstname);
    if (!query.exec()) {
        rollback(query);
        return 0;
    }

    query.exec(QString("SELECT " + MemberTable::COLUMNNAME[MemberTable::MemberId] + " FROM " + MemberTable::TABLENAME +
               " WHERE " + MemberTable::COLUMNNAME[MemberTable::Deleted] + " = 'true'" +
               " AND " + MemberTable::COLUMNNAME[MemberTable::EntryDate] + " = '" + date.toString(Qt::ISODate) + "'" +
               " AND " + MemberTable::COLUMNNAME[MemberTable::FirstName] + " = '%1'").arg(firstname));
    if (!query.next()) {
        rollback(query);
        return 0;
    }
    int id = query.value(0).toInt();

    QString insertInto = QString("INSERT INTO %1 (%2) VALUES (?)");
    query.prepare(insertInto
                  .arg(AddressTable::TABLENAME)
                  .arg(AddressTable::COLUMNNAME[AddressTable::MemberId]));
    query.addBindValue(id);
    if (!query.exec()) {
        rollback(query);
        return 0;
    }

    query.prepare(insertInto
                  .arg(BankAccountTable::TABLENAME)
                  .arg(BankAccountTable::COLUMNNAME[BankAccountTable::MemberId]));
    query.addBindValue(id);
    if (!query.exec()) {
        rollback(query);
        return 0;
    }

    query.prepare(insertInto
                  .arg(RessourcenTable::TABLENAME)
                  .arg(RessourcenTable::COLUMNNAME[RessourcenTable::MemberId]));
    query.addBindValue(id);
    if (!query.exec()) {
        rollback(query);
        return 0;
    }

    query.prepare(insertInto
                  .arg(ContributionTable::TABLENAME)
                  .arg(ContributionTable::COLUMNNAME[ContributionTable::MemberId]));
    query.addBindValue(id);
    if (!query.exec()) {
        rollback(query);
        return 0;
    }

    database.commit();
    return id;
}

void MemberDao::deleteMember(int aMemberId)
{
    const QString columnId = MemberTable::COLUMNNAME[MemberTable::MemberId];
    const QString whereClause = QString(" where %1 = %2").arg(columnId).arg(aMemberId);
    const QString columnDeteled = MemberTable::COLUMNNAME[MemberTable::Deleted];

    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause
                    + " AND " + columnDeteled + "='false'");
    /// \todo refactor if. Add a new parameter erease.
    if (query.next()) {
        query .exec("update " + MemberTable::TABLENAME + " set "
                    + columnDeteled + "='true' " + whereClause + " AND "
                    + columnDeteled + "='false'");
    } else {
        query.exec("delete from " + MemberTable::TABLENAME + whereClause);
        query.exec("delete from " + AddressTable::TABLENAME + whereClause);
        query.exec("delete from " + BankAccountTable::TABLENAME + whereClause);
        query.exec("delete from " + ContributionTable::TABLENAME + whereClause
                   + " AND " + ContributionTable::COLUMNNAME[ContributionTable::Fee] + " isNull AND " +
                   ContributionTable::COLUMNNAME[ContributionTable::Donation] + " isNull AND " +
                   ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " isNull AND" +
                   ContributionTable::COLUMNNAME[ContributionTable::Info] + " isNull");
        query.exec("delete from " + RessourcenTable::TABLENAME + whereClause);
    }

}

void MemberDao::rollback(const QSqlQuery &aQuery)
{
    printSqlError(aQuery.lastError());
    database.rollback();
}

bool MemberDao::saveRecordOnModel(QSqlTableModel *aTableModel, const QSqlRecord &aRecord)
{
    aTableModel->setRecord(0, aRecord);
    printSqlError(aTableModel->lastError());
    bool successful = aTableModel->submitAll();
    printSqlError(aTableModel->lastError());
    return successful;
}

QSqlRecord MemberDao::record(const QSqlTableModel *aTableModel)
{
    QSqlRecord record = aTableModel->record(0);
    printSqlError(aTableModel->lastError());
    return record;
}

void MemberDao::selectTableModel(QSqlTableModel *aModel, const QString &aColumnnameId, int aMemberId)
{
    QString filterId = QString("%1 = %2").arg(aColumnnameId).arg(aMemberId);
    aModel->setFilter(filterId);
    aModel->select();
}

void MemberDao::printSqlError(const QSqlError &anError)
{
    if (anError.type() != QSqlError::NoError) {
        /// \todo Publish error to the statusbar as event.
        qDebug() << anError.text();
    }
}

}
}
