#include "model/memberdao.h"
#include "model/databasestructure.h"

namespace ClubFrontend
{
namespace Model
{

MemberDao::MemberDao(const QSqlDatabase &aDatabase) :
    database(aDatabase)
{

}

MemberDao::~MemberDao()
{

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
    if(!query.exec()) {
        rollback(query);
        return 0;
    }

    query.exec("SELECT " + MemberTable::COLUMNNAME[MemberTable::MemberId] + " FROM " + MemberTable::TABLENAME +
               " WHERE " + MemberTable::COLUMNNAME[MemberTable::Deleted] + " = 'true'" +
               " AND " + MemberTable::COLUMNNAME[MemberTable::EntryDate] + " = '" + date.toString(Qt::ISODate) + "'" +
               " AND " + MemberTable::COLUMNNAME[MemberTable::FirstName] + " = 'newMember'");
    if(!query.next()) {
        rollback(query);
        return 0;
    }
    int id = query.value(0).toInt();

    QString insertInto = QString("INSERT INTO %1 (%2) VALUES (?)");
    query.prepare(insertInto
                  .arg(AddressTable::TABLENAME)
                  .arg(AddressTable::COLUMNNAME[AddressTable::MemberId]));
    query.addBindValue(id);
    if(!query.exec()) {
        rollback(query);
        return 0;
    }

    query.prepare(insertInto
                  .arg(BankAccountTable::TABLENAME)
                  .arg(BankAccountTable::COLUMNNAME[BankAccountTable::MemberId]));
    query.addBindValue(id);
    if(!query.exec()) {
        rollback(query);
        return 0;
    }

    query.prepare(insertInto
                  .arg(RessourcenTable::TABLENAME)
                  .arg(RessourcenTable::COLUMNNAME[RessourcenTable::MemberId]));
    query.addBindValue(id);
    if(!query.exec()) {
        rollback(query);
        return 0;
    }

    query.prepare(insertInto
                  .arg(ContributionTable::TABLENAME)
                  .arg(ContributionTable::COLUMNNAME[ContributionTable::MemberId]));
    query.addBindValue(id);
    if(!query.exec()) {
        rollback(query);
        return 0;
    }

    database.commit();
    return id;
}

void MemberDao::rollback(const QSqlQuery aQuery)
{
    QSqlError error = aQuery.lastError();
    if(error.type() != QSqlError::NoError) {
        qDebug() << error.text();
    }
    database.rollback();
}

void MemberDao::deleteMember(int anId)
{
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId]).arg(anId);
    const QString columnDeteled = MemberTable::COLUMNNAME[MemberTable::Deleted];

    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause
                    + " AND " + columnDeteled + "='false'");
    if(query.next()) {
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
