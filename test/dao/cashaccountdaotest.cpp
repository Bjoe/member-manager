
#include <QtTest/QtTest>

#include "testconfig.h"
#include "testcoverageobject.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace dao
{

class CashAccountDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testDao();
};

void CashAccountDaoTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void CashAccountDaoTest::testDao()
{
/*    membermanager::dao::KassaModel kassaModel(QSqlDatabase::database());

    using membermanager::dao::KassaTable;
    const QSqlTableModel *model = kassaModel.findChild<QSqlTableModel *> (KassaTable::TABLENAME);
    QVERIFY(model);
    QCOMPARE(model->rowCount(), 3);
    QSqlRecord record = model->record(1);
    QCOMPARE(record.value(KassaTable::betrag).toString(), QString("104.86"));
  */
}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::dao::CashAccountDaoTest)
#include "moc_cashaccountdaotest.cxx"
