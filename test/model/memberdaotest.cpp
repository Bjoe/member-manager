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

void MemberDaoTest::testGetRecordWithMemberId()
{
    using membermanager::model::MemberTable;
    membermanager::model::MemberDao dao(QSqlDatabase::database());
    QSqlRecord record = dao.getRecordWithMemberId(MemberTable::TABLENAME, 1026);
    QCOMPARE(record.value(MemberTable::FirstName).toString(), QString("Spock"));
}

void MemberDaoTest::testGetRecordWithMemberIdWithSort()
{
    using membermanager::model::ContributionTable;
    membermanager::model::MemberDao dao(QSqlDatabase::database());
    QSqlRecord record = dao.getRecordWithMemberId(ContributionTable::TABLENAME, 1025,
                        ContributionTable::ValidFrom, Qt::DescendingOrder);
    QCOMPARE(record.value(ContributionTable::Fee).toString(), QString("15"));
}

void MemberDaoTest::testSaveRecord()
{
    int id = 1026;
    using membermanager::model::MemberTable;
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(id);
    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause);
    query.exec();
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Spock"));

    membermanager::model::MemberDao dao(QSqlDatabase::database());
    QSqlRecord record = dao.getRecordWithMemberId(MemberTable::TABLENAME, id);
    QCOMPARE(record.value(MemberTable::FirstName).toString(), QString("Spock"));

    record.setValue(MemberTable::FirstName, QVariant("Spocky"));
    QVERIFY(dao.saveRecordWithMemberId(MemberTable::TABLENAME, id, record));

    query.exec();
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Spocky"));
}

void MemberDaoTest::testSaveRecordWithSort()
{
    int id = 1025;
    using membermanager::model::MemberTable;
    using membermanager::model::ContributionTable;
    const QString whereClause = QString(" where %1=%2 order by %3 desc").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(id).arg(ContributionTable::ValidFrom);
    QSqlQuery query("select * from " + ContributionTable::TABLENAME + whereClause);
    query.exec();
    query.last();
    QCOMPARE(query.value(ContributionTable::Fee).toString(), QString("15"));

    membermanager::model::MemberDao dao(QSqlDatabase::database());
    QSqlRecord record = dao.getRecordWithMemberId(ContributionTable::TABLENAME, id,
                        ContributionTable::ValidFrom, Qt::DescendingOrder);
    QCOMPARE(record.value(ContributionTable::Fee).toString(), QString("15"));

    record.setValue(ContributionTable::Fee, QVariant(23));
    QVERIFY(dao.saveRecordWithMemberId(ContributionTable::TABLENAME, id, record,
                                       ContributionTable::ValidFrom, Qt::DescendingOrder));

    query.exec();
    query.last();
    QCOMPARE(query.value(ContributionTable::Fee).toString(), QString("23"));
}

void MemberDaoTest::testSaveNewRecord()
{
    int id = 1026;
    using membermanager::model::MemberTable;
    QString whereClause = QString(" where %1=%2").arg(
                              MemberTable::COLUMNNAME[MemberTable::MemberId])
                          .arg(id);
    QSqlQuery query("select * from " + MemberTable::TABLENAME + whereClause);
    query.exec();
    query.next();
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Spock"));

    membermanager::model::MemberDao dao(QSqlDatabase::database());
    QSqlRecord record = dao.getRecordWithMemberId(MemberTable::TABLENAME, id);
    QCOMPARE(record.value(MemberTable::NickName).toString(), QString("Spock"));

    record.setValue(MemberTable::NickName, QVariant("Spitzohr"));
    record.setValue(MemberTable::MemberId, QVariant(1030));
    QVERIFY(dao.saveNewRecordWithMemberId(MemberTable::TABLENAME, id, record));

    id = 1030;
    whereClause = QString(" where %1=%2").arg(
                      MemberTable::COLUMNNAME[MemberTable::MemberId])
                  .arg(id);
    query = QSqlQuery("select * from " + MemberTable::TABLENAME + whereClause);

    query.exec();
    query.next();
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Spitzohr"));
}

}
}

QTEST_MAIN(membermanagertest::model::MemberDaoTest)
#include "memberdaotest.moc"
