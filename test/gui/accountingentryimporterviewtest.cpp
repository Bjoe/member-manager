#include <QtTest/QtTest>
#include "testcoverageobject.h"

#include "gui/accountingentryimporterview.h"

#include <QHeaderView>
#include <QTableWidget>

namespace membermanagertest
{
namespace gui
{

class AccountingEntryImporterViewTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testView();
};

void AccountingEntryImporterViewTest::initTestCase()
{
}

void AccountingEntryImporterViewTest::testView()
{
    membermanager::gui::AccountingEntryImporterView accountingEntryImportView;

    QTableWidget *tableWidget = accountingEntryImportView.getAccountingEntryTable();
    QCOMPARE(tableWidget->columnCount(), 9);
    QHeaderView *headerView = tableWidget->horizontalHeader();
    QCOMPARE(headerView->count(), 9);
    QCOMPARE(tableWidget->rowCount(), 0);
    QVERIFY(tableWidget->itemDelegateForColumn(1));
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::AccountingEntryImporterViewTest)
#include "moc_accountingentryimporterviewtest.cxx"
