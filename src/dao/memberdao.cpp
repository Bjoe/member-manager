#include "dao/memberdao.h"
#include "dao/databasestructure.h"

namespace membermanager
{
namespace dao
{

MemberDao::MemberDao(const QSqlDatabase &aDatabase, QObject *aParent) :
    database(aDatabase), parent(aParent)
{
}

bool MemberDao::saveRecord(const Member &aMember)
{
    int memberId = aMember.getMemberId();
    bool successful = true;

    QSqlRecord record = aMember.memberRecord;
    QString columnId = dao::MemberTable::COLUMNNAME[dao::MemberTable::MemberId];

    QSqlTableModel *memberModel = createMemberModel();
    selectTableModel(memberModel, columnId, memberId);
    successful &= saveRecordOnModel(memberModel, record);

    QSqlTableModel *resourceModel = createResourceModel();
    selectTableModel(resourceModel, dao::RessourcenTable::COLUMNNAME[dao::RessourcenTable::MemberId], memberId);
    record = aMember.resourceRecord;
    successful &= saveRecordOnModel(resourceModel, record);

    QSqlTableModel *bankModel = createBankModel();
    selectTableModel(bankModel, dao::BankAccountTable::COLUMNNAME[dao::BankAccountTable::MemberId], memberId);
    record = aMember.bankRecord;
    successful &= saveRecordOnModel(bankModel, record);

    QSqlTableModel *addressModel = createAddressModel();
    selectTableModel(addressModel, dao::AddressTable::COLUMNNAME[dao::AddressTable::MemberId], memberId);
    record = aMember.addressRecord;
    successful &= saveRecordOnModel(addressModel, record);

    delete memberModel;
    delete resourceModel;
    delete bankModel;
    delete addressModel;

    return successful;
}

Member MemberDao::findByMemberId(int aMemberId)
{
    Member member;

    QSqlTableModel *addressModel = createAddressModel();
    selectTableModel(addressModel, dao::AddressTable::COLUMNNAME[dao::AddressTable::MemberId], aMemberId);
    member.addressRecord = record(addressModel);

    QSqlTableModel *bankModel = createBankModel();
    selectTableModel(bankModel, dao::BankAccountTable::COLUMNNAME[dao::BankAccountTable::MemberId], aMemberId);
    member.bankRecord = record(bankModel);

    QSqlTableModel *resourceModel = createResourceModel();
    selectTableModel(resourceModel, dao::RessourcenTable::COLUMNNAME[dao::RessourcenTable::MemberId], aMemberId);
    member.resourceRecord = record(resourceModel);

    QSqlTableModel *memberModel = createMemberModel();
    selectTableModel(memberModel, dao::MemberTable::COLUMNNAME[dao::MemberTable::MemberId], aMemberId);
    member.memberRecord = record(memberModel);

    delete memberModel;
    delete resourceModel;
    delete bankModel;
    delete addressModel;

    return member;
}

QSqlTableModel *MemberDao::modelSelectDeleted(bool isDeleted)
{
    QSqlTableModel* memberModel = createMemberModel();
    selectDeleted(memberModel, isDeleted);
    return memberModel;
}

QList<Member> MemberDao::findByDeleted(bool isDeleted)
{
    QSqlTableModel* memberModel = createMemberModel();
    selectDeleted(memberModel, isDeleted);

    QList<Member> list;
    int rowCount = memberModel->rowCount();
    for(int row = 0; rowCount > row; row++) {
        QModelIndex index = memberModel->index(row, dao::MemberTable::MemberId);
        QVariant variant = index.data();
        Member member = findByMemberId(variant.toInt());
        list.append(member);
    }

    delete memberModel;
    return list;
}

void MemberDao::selectDeleted(QSqlTableModel *aModel, bool isDeleted)
{
    QString deleted = "'false'";
    if(isDeleted) {
        deleted = "'true'";
    }

    QString columnname = dao::MemberTable::COLUMNNAME[dao::MemberTable::Deleted];
    QString filter = QString("%1 = %2").arg(columnname).arg(deleted);

    aModel->setFilter(filter);
    aModel->select();
}

QSqlTableModel *MemberDao::createMemberModel()
{
    QSqlTableModel *memberModel = new QSqlTableModel(parent, database);
    memberModel->setTable(dao::MemberTable::TABLENAME);
    memberModel->setObjectName(dao::MemberTable::TABLENAME);
    memberModel->setHeaderData(MemberTable::MemberId, Qt::Horizontal, memberModel->tr("Nr."));
    memberModel->setHeaderData(MemberTable::FirstName, Qt::Horizontal, memberModel->tr("Vorname"));
    memberModel->setHeaderData(MemberTable::Name, Qt::Horizontal, memberModel->tr("Name"));
    memberModel->setHeaderData(MemberTable::NickName, Qt::Horizontal, memberModel->tr("Nickname"));
    memberModel->setHeaderData(MemberTable::EntryDate, Qt::Horizontal, memberModel->tr("Eintritts Datum"));
    return memberModel;
}

QSqlTableModel *MemberDao::createResourceModel()
{
    QSqlTableModel *resourceModel = new QSqlTableModel(parent, database);
    resourceModel->setTable(dao::RessourcenTable::TABLENAME);
    resourceModel->setObjectName(dao::RessourcenTable::TABLENAME);
    return resourceModel;
}

QSqlTableModel* MemberDao::createBankModel()
{
    QSqlTableModel *bankModel = new QSqlTableModel(parent, database);
    bankModel->setTable(dao::BankAccountTable::TABLENAME);
    bankModel->setObjectName(dao::BankAccountTable::TABLENAME);
    return bankModel;
}

QSqlTableModel* MemberDao::createAddressModel()
{
    QSqlTableModel *addressModel = new QSqlTableModel(parent, database);
    addressModel->setTable(dao::AddressTable::TABLENAME);
    addressModel->setObjectName(dao::AddressTable::TABLENAME);
    return addressModel;
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

int MemberDao::createMember()
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

}
}
