#include "contributionmodeltest.h"

#include "model/contributionmodel.h"

#include "testconfig.h"
#include "database/databaseutil.h"
#include "model/databasestructure.h"
#include "model/memberfilter.h"

#include <QSqlTableModel>
#include <QSqlRecord>
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
    MemberFilter filter = MemberFilter::build().withMemberId(1025);
    membermanager::model::ContributionModel contributionModel(filter, QSqlDatabase::database());

    using membermanager::model::ContributionTable;
    const QSqlTableModel *model = contributionModel.findChild<QSqlTableModel *> (ContributionTable::TABLENAME);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 2);
    QSqlRecord record = model->record(0);
    QCOMPARE(record.value(ContributionTable::Info).toString(), QString("Beitragsaenderung"));
    QCOMPARE(record.value(ContributionTable::Fee).toString(), QString("15"));
}

}
}

QTEST_MAIN(membermanagertest::model::ContributionModelTest)
#include "contributionmodeltest.moc"
