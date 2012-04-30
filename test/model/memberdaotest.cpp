#include "memberdaotest.h"

#include "model/memberdao.h"

#include "testconfig.h"
#include "model/databasestructure.h"
#include "database/databaseutil.h"

#include "member.h"

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

void MemberDaoTest::testFindByMemberId()
{
    membermanager::model::MemberDao memberDao(QSqlDatabase::database());

    membermanager::Member member = memberDao.findByMemberId(1025);

    QCOMPARE(member.getName(), QString("Kirk"));
}

void MemberDaoTest::testFindByRow()
{
    membermanager::model::MemberDao memberDao(QSqlDatabase::database());

    membermanager::Member member = memberDao.findByRow(1);

    QCOMPARE(member.getName(), QString("Spock"));
}

void MemberDaoTest::testGetModel()
{
    membermanager::model::MemberDao memberDao(QSqlDatabase::database());

    QSqlTableModel *model = memberDao.model();
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value("name").toString(), QString("Kirk"));
}

void MemberDaoTest::testNewMember()
{
    membermanager::model::MemberDao dao(QSqlDatabase::database());
    int id = dao.newMember();
    QVERIFY(id);

    using membermanager::model::MemberTable;
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(id);
    const QString select = QString("select * from ");
    QSqlQuery query;

    query.exec(select + MemberTable::TABLENAME + whereClause);
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

void MemberDaoTest::testSaveRecord()
{
    membermanager::model::MemberDao dao(QSqlDatabase::database());
    membermanager::Member member = dao.findByMemberId(1025);

    QCOMPARE(member.getMemberId(), 1025);
    QCOMPARE(member.getName(), QString("Kirk"));
    QCOMPARE(member.getFirstname(), QString("James T"));
    QCOMPARE(member.getNickname(), QString("Capt. Kirk"));
    QCOMPARE(member.getEntryDate(), QDate(2001, 4, 24));
    QCOMPARE(member.getInfo(), QString("Captain of the ncc-1701"));
    QCOMPARE(member.getEmail(), QString("fooo@baaar.xx"));
    QCOMPARE(member.getStreet(), QString("Industriestr. 23"));
    QCOMPARE(member.getCity(), QString("Bloedeldorf"));
    QCOMPARE(member.getZipCode(), QString("90546"));
    QCOMPARE(member.getAccountNr(), QString("12234569"));
    QCOMPARE(member.getBankName(), QString("sparstrumpf"));
    QCOMPARE(member.getCode(), QString("9004010"));
    QCOMPARE(member.getReference(), QString("2193"));
    QVERIFY(member.isCollection() == true);
    QVERIFY(member.isDeleted() == false);

    member.setName("Archer");
    member.setFirstname("Jonathan");
    member.setNickname("Captain");
    member.setStreet("NCC-1701");
    member.setCity("Dtown");
    member.setZipCode("98765");
    member.setEmail("foo@bar.tx");
    member.setEntryDate(QDate(2006, 07, 15));
    member.setAccountNr("123456789");
    member.setBankName("Galaxy");
    member.setCode("98765432");
    member.setInfo("Lalala");
    member.setReference("9876");
    member.setCollection(false);
    member.setDeleted(false);

    QVERIFY(dao.saveRecord(member));

    const QString whereClause(" where dorfmitglied_pkey=1025");

    using membermanager::model::MemberTable;
    QSqlQuery query;
    query.exec("select * from " + MemberTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
    QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
    QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));
    QCOMPARE(query.value(MemberTable::FOO_ChaosNr).toString(), QString("9876"));
    QVERIFY(query.value(MemberTable::FOO_Einzug).toBool() == false);
    QVERIFY(query.value(MemberTable::Deleted).toBool() == false);

    using membermanager::model::AddressTable;
    query.exec("select * from " + AddressTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
    QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
    QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

    using membermanager::model::BankAccountTable;
    query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
    QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
    QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

    using membermanager::model::RessourcenTable;
    query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

void MemberDaoTest::testDeleteMember()
{
    int id = 1025;
    using membermanager::model::MemberTable;
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(id);
    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause);

    query.exec();
    query.next();
    QVERIFY(!query.value(MemberTable::Deleted).toBool());

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
