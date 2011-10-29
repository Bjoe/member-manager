#include "memberdaotest.h"

#include "model/memberdao.h"

#include "testconfig.h"
#include "model/databasestructure.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace model
{

void MemberDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberDaoTest::testNewMember()
{
    membermanager::model::MemberDao dao(QSqlDatabase::database());
    int id = dao.newMember();
    QVERIFY(id);

    const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(id);
    const QString select = QString("select * from ");
    QSqlQuery query;

    query.exec(select + membermanager::model::MemberTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + membermanager::model::AddressTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + membermanager::model::BankAccountTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + membermanager::model::ContributionTable::TABLENAME + whereClause);
    QVERIFY(query.next());

    query.exec(select + membermanager::model::RessourcenTable::TABLENAME + whereClause);
    QVERIFY(query.next());
}

void MemberDaoTest::testDeleteMember()
{
    int id = 1025;
    const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(id);
    using membermanager::model::MemberTable;
    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause);

    membermanager::model::MemberDao dao(QSqlDatabase::database());
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

QTEST_MAIN(membermanagertest::model::MemberDaoTest)
#include "memberdaotest.moc"
