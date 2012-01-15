#include "contributionmodeltest.h"

#include "model/contributionmodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"
#include "model/memberfilter.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QString>
#include <QVariant>

namespace membermanagertest
{
namespace model
{

void ContributionModelTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionModelTest::testModel()
{
    using membermanager::model::MemberFilter;
    membermanager::model::ContributionModel contributionModel(1025, QSqlDatabase::database(), this);

    using membermanager::model::ContributionTable;
    const QSqlTableModel *model = contributionModel.getModel();
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(ContributionTable::Info -1).toString(), QString("Beitragsaenderung"));
    QCOMPARE(record.value(ContributionTable::Fee).toString(), QString("15"));
}

void ContributionModelTest::testGetMemberId()
{
    using membermanager::model::MemberFilter;
    membermanager::model::ContributionModel contributionModel(1025, QSqlDatabase::database());

    QCOMPARE(contributionModel.getMemberId(), 1025);
}

void ContributionModelTest::testInsertAndDeleteRow()
{
    using membermanager::model::MemberFilter;
    membermanager::model::ContributionModel contributionModel(1025, QSqlDatabase::database(), this);

    using membermanager::model::ContributionTable;
    QSqlTableModel *model = contributionModel.getModel();
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);

    QModelIndex index = contributionModel.insertNewRow();

    QCOMPARE(index.row(), 2);
    model->select();
    QCOMPARE(model->rowCount(), 3);

    QVERIFY(contributionModel.deleteRow(index));

    model->select();
    QCOMPARE(model->rowCount(), 2);
}

}
}

QTEST_MAIN(membermanagertest::model::ContributionModelTest)
#include "contributionmodeltest.moc"
