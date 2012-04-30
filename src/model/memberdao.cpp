#include "model/memberdao.h"
#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

MemberDao::MemberDao(const QSqlDatabase &aDatabase, QObject *aParent) :
    database(aDatabase),
    memberModel(new QSqlTableModel(aParent, aDatabase)),
    ressourcenModel(new QSqlTableModel(aParent, aDatabase)),
    bankModel(new QSqlTableModel(aParent, aDatabase)),
    addressModel(new QSqlTableModel(aParent, aDatabase))
{
    memberModel->setTable(model::MemberTable::TABLENAME);
    memberModel->setObjectName(model::MemberTable::TABLENAME);
    memberModel->select();

    ressourcenModel->setTable(model::RessourcenTable::TABLENAME);
    ressourcenModel->setObjectName(model::RessourcenTable::TABLENAME);

    bankModel->setTable(model::BankAccountTable::TABLENAME);
    bankModel->setObjectName(model::BankAccountTable::TABLENAME);

    addressModel->setTable(model::AddressTable::TABLENAME);
    addressModel->setObjectName(model::AddressTable::TABLENAME);
}

bool MemberDao::saveRecord(const Member &aMember)
{
    int memberId = aMember.getMemberId();
    bool successful = true;

    QSqlRecord record = aMember.memberRecord;
    QString columnId = model::MemberTable::COLUMNNAME[model::MemberTable::MemberId];
    selectTableModel(memberModel, columnId, memberId);
    successful &= saveRecordOnModel(memberModel, record);

    selectTableModel(ressourcenModel, model::RessourcenTable::COLUMNNAME[model::RessourcenTable::MemberId], memberId);
    record = aMember.ressourcenRecord;
    successful &= saveRecordOnModel(ressourcenModel, record);

    selectTableModel(bankModel, model::BankAccountTable::COLUMNNAME[model::BankAccountTable::MemberId], memberId);
    record = aMember.bankRecord;
    successful &= saveRecordOnModel(bankModel, record);

    selectTableModel(addressModel, model::AddressTable::COLUMNNAME[model::AddressTable::MemberId], memberId);
    record = aMember.addressRecord;
    successful &= saveRecordOnModel(addressModel, record);

    return successful;
}

Member MemberDao::findByMemberId(int aMemberId)
{
    Member member;

    selectTableModel(addressModel, model::AddressTable::COLUMNNAME[model::AddressTable::MemberId], aMemberId);
    member.addressRecord = record(addressModel);

    selectTableModel(bankModel, model::BankAccountTable::COLUMNNAME[model::BankAccountTable::MemberId], aMemberId);
    member.bankRecord = record(bankModel);

    selectTableModel(ressourcenModel, model::RessourcenTable::COLUMNNAME[model::RessourcenTable::MemberId], aMemberId);
    member.ressourcenRecord = record(ressourcenModel);

    selectTableModel(memberModel, model::MemberTable::COLUMNNAME[model::MemberTable::MemberId], aMemberId);
    member.memberRecord = record(memberModel);

    return member;
}

Member MemberDao::findByRow(int aRowNr)
{
    Member member;

    member.memberRecord = memberModel->record(aRowNr);

    int memberId = member.getMemberId();
    selectTableModel(bankModel, model::BankAccountTable::COLUMNNAME[model::BankAccountTable::MemberId], memberId);
    member.bankRecord = record(bankModel);

    selectTableModel(ressourcenModel, model::RessourcenTable::COLUMNNAME[model::RessourcenTable::MemberId], memberId);
    member.ressourcenRecord = record(ressourcenModel);

    selectTableModel(memberModel, model::MemberTable::COLUMNNAME[model::MemberTable::MemberId], memberId);
    member.memberRecord = record(memberModel);

    return member;
}

QList<Member> MemberDao::findByDeleted(bool isDeleted)
{
    QString deleted = "'false'";
    if(isDeleted) {
        deleted = "'true'";
    }

    QString columnname = model::MemberTable::COLUMNNAME[model::MemberTable::Deleted];
    QString filter = QString("%1 = %2").arg(columnname).arg(deleted);

    QSqlTableModel *tableModel = model();
    tableModel->setFilter(filter);
    tableModel->select();

    QList<Member> list;
    for(int row = 0; row < tableModel->rowCount(); row++) {
        QModelIndex index = tableModel->index(row, model::MemberTable::MemberId);
        QVariant variant = index.data();
        Member member = findByMemberId(variant.toInt());
        list.append(member);
    }
    return list;
}

QSqlTableModel *MemberDao::model()
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable(model::MemberTable::TABLENAME);
    model->setObjectName(model::MemberTable::TABLENAME);
    model->setHeaderData(MemberTable::MemberId, Qt::Horizontal, memberModel->tr("Nr."));
    model->setHeaderData(MemberTable::FirstName, Qt::Horizontal, memberModel->tr("Vorname"));
    model->setHeaderData(MemberTable::Name, Qt::Horizontal, memberModel->tr("Name"));
    model->setHeaderData(MemberTable::NickName, Qt::Horizontal, memberModel->tr("Nickname"));
    model->setHeaderData(MemberTable::EntryDate, Qt::Horizontal, memberModel->tr("Eintritts Datum"));
    model->select();

    return model;
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
