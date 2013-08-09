#include "paymentviewtest.h"

#include "gui/paymentview.h"

#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QList>

#include "testconfig.h"
#include "database/databaseutil.h"

#include "accounting/balanceentry.h"
#include "dao/balancedao.h"

namespace membermanagertest
{
namespace gui
{

void PaymentViewTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void PaymentViewTest::testCalculate()
{
    QSettings settings;
    settings.setValue("bank/name", QString("foobar"));
    settings.setValue("bank/code", QString("39912399"));
    settings.setValue("bank/account", QString("123456"));

    membermanager::gui::PaymentView paymentView;

    QTableWidget *tableWidget = paymentView.findChild<QTableWidget *>("tableWidget");
    QLineEdit *lineEdit = paymentView.findChild<QLineEdit *>("lineEdit");
    QPushButton *calculateButton = paymentView.findChild<QPushButton *>("calculateButton");
    QPushButton *bookingButton = paymentView.findChild<QPushButton *>("bookingButton");

    QCOMPARE(tableWidget->rowCount(), 0);

    QTest::mouseClick(calculateButton, Qt::LeftButton);

    QCOMPARE(tableWidget->rowCount(), 3);

    QTableWidgetItem *item1 = tableWidget->item(1,0);
    QCOMPARE(item1->text(), QString("1030"));
    QTableWidgetItem *item2 = tableWidget->item(1,1);
    QCOMPARE(item2->text(), QString("Montgomery"));
    QTableWidgetItem *item3 = tableWidget->item(1,2);
    QCOMPARE(item3->text(), QString("Scott"));
    QTableWidgetItem *item4 = tableWidget->item(1,3);
    QCOMPARE(item4->text(), lineEdit->text());
    QTableWidgetItem *item5 = tableWidget->item(1,4);
    QVERIFY(item5->checkState() == Qt::Checked);
    item5->setCheckState(Qt::Unchecked);

    QTest::mouseClick(bookingButton, Qt::LeftButton);

    membermanager::dao::BalanceDao balanceDao;
    QList<membermanager::accounting::BalanceEntry> list = balanceDao.findByMemberId(1033);
    QCOMPARE(list.size(), 2);

    list = balanceDao.findByMemberId(1030);
    QCOMPARE(list.size(), 0);
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::PaymentViewTest)
#include "moc_paymentviewtest.cpp"
