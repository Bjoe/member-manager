#include <QtTest/QtTest>
#include "testconfig.h"
#include "testcoverageobject.h"
#include "database/databaseutil.h"

#include "gui/accountingentryimporterview.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QPushButton>

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
    void testImport();
    void testBooked();
};

void AccountingEntryImporterViewTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void AccountingEntryImporterViewTest::testView()
{
    membermanager::gui::AccountingEntryImporterView accountingEntryImportView;

    QTableWidget *tableWidget = accountingEntryImportView.findChild<QTableWidget *>("tableWidget");
    QCOMPARE(tableWidget->columnCount(), 10);
    QHeaderView *headerView = tableWidget->horizontalHeader();
    QCOMPARE(headerView->count(), 10);
    QCOMPARE(tableWidget->rowCount(), 7);
    QVERIFY(tableWidget->itemDelegateForColumn(1));
}

void AccountingEntryImporterViewTest::testImport()
{
    membermanager::gui::AccountingEntryImporterView accountingEntryImportView;

    QPushButton *importButton = accountingEntryImportView.findChild<QPushButton *>("importButton");
    //QTest::mouseClick(importButton, Qt::LeftButton); How can test with QFileDialog ...
}

void AccountingEntryImporterViewTest::testBooked()
{
    membermanager::gui::AccountingEntryImporterView accountingEntryImportView;

    QPushButton *bookingButton = accountingEntryImportView.findChild<QPushButton *>("bookingButton");

}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::AccountingEntryImporterViewTest)
#include "moc_accountingentryimporterviewtest.cpp"
