
#include <QtTest/QtTest>

#include "accounting/accountingentryimportermain.h"

#include "testcoverageobject.h"
#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace accounting
{

class AccountingEntryImporterMainTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testMain();
};

void AccountingEntryImporterMainTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void AccountingEntryImporterMainTest::testMain()
{
   membermanager::accounting::AccountingEntryImporterMain *main = new membermanager::accounting::AccountingEntryImporterMain();

}

} // namespace accounting
} // namespace membermanagertest


QTEST_MAIN(membermanagertest::accounting::AccountingEntryImporterMainTest)
#include "moc_accountingentryimportermaintest.cxx"

