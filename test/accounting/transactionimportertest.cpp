
#include <QtTest/QtTest>

#include "testcoverageobject.h"
#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace accounting
{

class TransactionImporterTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testImport();
};

void TransactionImporterTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void TransactionImporterTest::testImport()
{

}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::accounting::TransactionImporterTest)
#include "moc_transactionimportertest.cxx"
