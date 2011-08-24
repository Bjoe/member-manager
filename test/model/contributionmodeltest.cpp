#include "contributionmodeltest.h"

#include "model/contributionmodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>
#include <QVariant>

namespace ClubFrontendTest
{
namespace Model
{

void ContributionModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionModelTest::testModel()
{
    ClubFrontend::Model::ContributionModel contributionModel(QSqlDatabase::database());

    contributionModel.setMemberId(1025);
    using ClubFrontend::Model::ContributionTable;
    const QSqlTableModel *model = contributionModel.findChild<QSqlTableModel *> (ContributionTable::TABLENAME);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(ContributionTable::Info).toString(), QString("Beitragsaenderung"));
    QCOMPARE(record.value(ContributionTable::Fee).toString(), QString("15"));
}

void ContributionModelTest::testGetColumns()
{
    ClubFrontend::Model::ContributionModel contributionModel(QSqlDatabase::database());

    contributionModel.setMemberId(1025);
    QCOMPARE(contributionModel.getInfo(), QString("Beitragsaenderung"));
    QCOMPARE(contributionModel.getDonation(), QString("1"));
    QCOMPARE(contributionModel.getFee(), QString("15"));
}

void ContributionModelTest::testChangeInfo()
{
    ClubFrontend::Model::ContributionModel contributionModel(QSqlDatabase::database());

    contributionModel.setMemberId(1025);

    contributionModel.submit("15", "1", "Foo");

    QCOMPARE(contributionModel.getDonation(), QString("1"));
    QCOMPARE(contributionModel.getFee(), QString("15"));
    QCOMPARE(contributionModel.getInfo(), QString("Foo"));
}

void ContributionModelTest::testNewFeeDonation()
{
    ClubFrontend::Model::ContributionModel contributionModel(QSqlDatabase::database());

    contributionModel.setMemberId(1025);

    using ClubFrontend::Model::ContributionTable;
    QSqlTableModel *model = contributionModel.findChild<QSqlTableModel *> (ContributionTable::TABLENAME);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);

    contributionModel.submit("90", "50", "bar");

    QCOMPARE(model->rowCount(), 3);

    contributionModel.refresh();
    QCOMPARE(contributionModel.getDonation(), QString("50"));
    QCOMPARE(contributionModel.getFee(), QString("90"));
    QCOMPARE(contributionModel.getInfo(), QString("bar"));

    const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(1025);
    QSqlQuery query;
    query.exec("select * from " + ContributionTable::TABLENAME + whereClause +
               " order by " + ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " desc");
    query.next();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 90);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 50);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("bar"));

    //! \todo Test auf ValidFrom mit QDate::currentDate()
}

void ContributionModelTest::testNewMemberId()
{
    QSqlTableModel *tableModel = new QSqlTableModel();
    tableModel->setTable(ClubFrontend::Model::ContributionTable::TABLENAME);
    tableModel->select();
    QCOMPARE(tableModel->rowCount(), 3);

    ClubFrontend::Model::ContributionModel contributionModel(QSqlDatabase::database());
    QVariant id(123);
    int row = contributionModel.insertMemberId(id);
    QCOMPARE(row , 3);

    tableModel->select();
    QCOMPARE(tableModel->rowCount(), 4);
    const QString whereClause = QString(" where dorfmitglied_pkey=%1").arg(123);
    QSqlQuery query;
    using ClubFrontend::Model::ContributionTable;
    query.exec("select * from " + ContributionTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(ContributionTable::MemberId).toInt(), 123);
}

}
}

QTEST_MAIN(ClubFrontendTest::Model::ContributionModelTest)
#include "contributionmodeltest.moc"
