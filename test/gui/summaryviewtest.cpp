#include "summaryviewtest.h"

#include "gui/summaryview.h"

#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

void SummaryViewTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void SummaryViewTest::testSummary()
{
    membermanager::gui::SummaryView summaryView;

    QLabel *totalCash = summaryView.findChild<QLabel *>("totalCash");
    QLabel *totalDonation = summaryView.findChild<QLabel *>("totalDonation");
    QLabel *totalCollection = summaryView.findChild<QLabel *>("totalCollection");
    QLabel *totalSaldo = summaryView.findChild<QLabel *>("totalSaldo");
    QLabel *totalMembers = summaryView.findChild<QLabel *>("totalMembers");
    QLabel *totalMemberCollection = summaryView.findChild<QLabel *>("totalMemberCollection");
    QLabel *totalMemberDonation = summaryView.findChild<QLabel *>("totalMemberDonation");
    QTableWidget *tableWidget = summaryView.findChild<QTableWidget *>("tableWidget");
    QPushButton *pushButton = summaryView.findChild<QPushButton *>("pushButton");

    QCOMPARE(totalCash->text(), QString("-,- Euro"));
    QCOMPARE(totalDonation->text(), QString("-,- Euro"));
    QCOMPARE(totalCollection->text(), QString("-,- Euro"));
    QCOMPARE(totalSaldo->text(), QString("-,- Euro"));
    QCOMPARE(totalMembers->text(), QString("0"));
    QCOMPARE(totalMemberCollection->text(), QString("0"));
    QCOMPARE(totalMemberDonation->text(), QString("0"));
    QCOMPARE(tableWidget->rowCount(), 0);

    QTest::mouseClick(pushButton, Qt::LeftButton);

    QCOMPARE(totalCash->text(), QString(" 100,50 Euro"));
    QCOMPARE(totalDonation->text(), QString("   1,50 Euro"));
    QCOMPARE(totalCollection->text(), QString(" 100,50 Euro"));
    QCOMPARE(totalSaldo->text(), QString(" -10,00 Euro"));
    QCOMPARE(totalMembers->text(), QString("3"));
    QCOMPARE(totalMemberCollection->text(), QString("2"));
    QCOMPARE(totalMemberDonation->text(), QString("1"));
    QCOMPARE(tableWidget->rowCount(), 2);

    QTableWidgetItem *item1 = tableWidget->item(1,0);
    QCOMPARE(item1->text(), QString("1"));
    QTableWidgetItem *item2 = tableWidget->item(1,1);
    QCOMPARE(item2->text(), QString("  99,00 Euro"));
    QTableWidgetItem *item3 = tableWidget->item(1,2);
    QCOMPARE(item3->text(), QString("=    99,00 Euro"));
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::SummaryViewTest)
#include "summaryviewtest.moc"
