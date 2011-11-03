#include "model/memberdao.h"

namespace membermanager
{
namespace model
{

/// \todo constructor(Object, database)
MemberDao::MemberDao(const QSqlDatabase &aDatabase) :
    object(new QObject()), database(aDatabase),  pkey(model::MemberTable::COLUMNNAME[model::MemberTable::MemberId])

{
}

QSqlRecord MemberDao::getRecordWithMemberId(const QString &aTableName, int anId,
        int aSortColumn, Qt::SortOrder aSortOrder)
{
    QSqlTableModel model(object, database);
    selectTableModel(model, aTableName, anId, aSortColumn, aSortOrder);
    QSqlRecord record = model.record(0);
    printSqlError(model.lastError());
    return record;
}

bool MemberDao::saveRecordWithMemberId(const QString &aTableName, const QSqlRecord &aRecord,
                                       int aSortColumn, Qt::SortOrder aSortOrder)
{
    QSqlTableModel model(object, database);
    selectTableModel(model, aTableName, aRecord.value(pkey).toInt(), aSortColumn, aSortOrder);
    model.setRecord(0, aRecord);
    printSqlError(model.lastError());
    bool successful = model.submitAll();
    printSqlError(model.lastError());
    return successful;
}

bool MemberDao::saveNewRecordWithMemberId(const QString &aTableName, const QSqlRecord &aRecord,
        int aSortColumn, Qt::SortOrder aSortOrder)
{
    QSqlTableModel model(object, database);
    selectTableModel(model, aTableName, aRecord.value(pkey).toInt(), aSortColumn, aSortOrder);
    bool successful = model.insertRecord(-1, aRecord);
    printSqlError(model.lastError());
    return successful;
}

void MemberDao::selectTableModel(QSqlTableModel &aModel, const QString &aTableName, int anId,
                                 int aSortColumn, Qt::SortOrder aSortOrder)
{
    const QString filter = QString(pkey + " = %1").arg(anId);

    aModel.setTable(aTableName);
    aModel.setFilter(filter);
    if (aSortColumn != -1)
        aModel.setSort(aSortColumn, aSortOrder);
    aModel.select();
}

int MemberDao::newMember()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QDate date = dateTime.date();

    database.transaction();
    QSqlQuery query(database);

    query.prepare("INSERT INTO " + MemberTable::TABLENAME +
                  " (" + MemberTable::COLUMNNAME[MemberTable::Deleted] +
                  " ," + MemberTable::COLUMNNAME[MemberTable::EntryDate] +
                  " ," + MemberTable::COLUMNNAME[MemberTable::FirstName] +
                  ") VALUES (? ,? ,? )");
    query.addBindValue("true");
    query.addBindValue(date.toString(Qt::ISODate));
    query.addBindValue("newMember");
    if (!query.exec()) {
        rollback(query);
        return 0;
    }

    query.exec("SELECT " + MemberTable::COLUMNNAME[MemberTable::MemberId] + " FROM " + MemberTable::TABLENAME +
               " WHERE " + MemberTable::COLUMNNAME[MemberTable::Deleted] + " = 'true'" +
               " AND " + MemberTable::COLUMNNAME[MemberTable::EntryDate] + " = '" + date.toString(Qt::ISODate) + "'" +
               " AND " + MemberTable::COLUMNNAME[MemberTable::FirstName] + " = 'newMember'");
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

void MemberDao::deleteMember(int anId)
{
    const QString whereClause = QString(" where %1=%2").arg(pkey).arg(anId);
    const QString columnDeteled = MemberTable::COLUMNNAME[MemberTable::Deleted];

    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause
                    + " AND " + columnDeteled + "='false'");
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

void MemberDao::printSqlError(const QSqlError &anError)
{
    if (anError.type() != QSqlError::NoError) {
        /// \todo Publish error to the statusbar as event.
        qDebug() << anError.text();
    }
}

}
}
