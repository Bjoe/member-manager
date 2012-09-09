#include "accountingentryimporterviewtest.h"

#include "gui/accountingentryimporterview.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

void AccountingEntryImporterViewTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void AccountingEntryImporterViewTest::testImport()
{
    membermanager::gui::AccountingEntryImporterView accountingEntryImportView;
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::AccountingEntryImporterViewTest)
#include "accountingentryimporterviewtest.moc"
