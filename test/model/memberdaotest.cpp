#include "memberdaotest.h"

#include "model/memberdao.h"

#include "testconfig.h"
#include "model/databasestructure.h"
#include "database/databaseutil.h"

namespace ClubFrontendTest
{
namespace Model
{

void MemberDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberDaoTest::testNewMember()
{
    ClubFrontend::Model::MemberDao dao(QSqlDatabase::database());
    int id = dao.newMember();
    QVERIFY(id);

    const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(id);
    const QString select = QString("select * from ");
    QSqlQuery query;

    query.exec(select + ClubFrontend::Model::MemberTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + ClubFrontend::Model::AddressTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + ClubFrontend::Model::BankAccountTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + ClubFrontend::Model::ContributionTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + ClubFrontend::Model::RessourcenTable::TABLENAME + whereClause);
    QVERIFY(query.next());
}

void MemberDaoTest::testDeleteMember()
{
    int id = 1025;
    const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(id);
    using ClubFrontend::Model::MemberTable;
    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause);

    ClubFrontend::Model::MemberDao dao(QSqlDatabase::database());
    dao.deleteMember(id);

    query.exec();
    query.next();
    QVERIFY(query.value(MemberTable::Deleted).toBool());

    dao.deleteMember(id);

    query.exec();
    QVERIFY(!query.next());
}

}
}

QTEST_MAIN(ClubFrontendTest::Model::MemberDaoTest)
#include "memberdaotest.moc"
