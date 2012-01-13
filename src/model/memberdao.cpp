#include "model/memberdao.h"
#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

/// \todo constructor(Object, database)
MemberDao::MemberDao(const QSqlDatabase &aDatabase) :
    object(new QObject()), database(aDatabase),  pkey(model::MemberTable::COLUMNNAME[model::MemberTable::MemberId])

{
}

QSqlRecord MemberDao::getRecordWithMemberId(const QString &aTableName, const MemberFilter &aFilter
        , int aSortColumn, Qt::SortOrder aSortOrder)
{
    QSqlTableModel model(object, database);
    selectTableModel(model, aTableName, aFilter, aSortColumn, aSortOrder);
    QSqlRecord record = model.record(0);
    printSqlError(model.lastError());
    return record;
}

bool MemberDao::saveRecordWithMemberId(const QString &aTableName, const MemberFilter &aFilter
                                       , const QSqlRecord &aRecord, int aSortColumn, Qt::SortOrder aSortOrder)
{
    QSqlTableModel model(object, database);
    selectTableModel(model, aTableName, aFilter, aSortColumn, aSortOrder);
    model.setRecord(0, aRecord);
    printSqlError(model.lastError());
    bool successful = model.submitAll();
    printSqlError(model.lastError());
    return successful;
}

bool MemberDao::saveNewRecordWithMemberId(const QString &aTableName, const MemberFilter &aFilter
        , const QSqlRecord &aRecord, int aSortColumn, Qt::SortOrder aSortOrder)
{
    QSqlTableModel model(object, database);
    selectTableModel(model, aTableName, aFilter, aSortColumn, aSortOrder);
    bool successful = model.insertRecord(-1, aRecord);
    printSqlError(model.lastError());
    return successful;
}

void MemberDao::selectTableModel(QSqlTableModel &aModel, const QString &aTableName, const MemberFilter &aFilter
                                 , int aSortColumn, Qt::SortOrder aSortOrder)
{
    aModel.setTable(aTableName);
    aModel.setFilter(aFilter.createFilter());
    if (aSortColumn != -1)
        aModel.setSort(aSortColumn, aSortOrder);
    aModel.select();
}

int MemberDao::newMember()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QDate date = dateTime.date();
    QString firstname = QString("newMember%1").arg(dateTime.toMSecsSinceEpoch());
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

void MemberDao::deleteMember(const MemberFilter &aFilter)
{
    const QString whereClause = QString(" where %1").arg(aFilter.createFilter());
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

void MemberDao::printSqlError(const QSqlError &anError)
{
    if (anError.type() != QSqlError::NoError) {
        /// \todo Publish error to the statusbar as event.
        qDebug() << anError.text();
    }
}

}
}
