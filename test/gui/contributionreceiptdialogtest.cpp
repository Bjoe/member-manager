#include "contributionreceiptdialogtest.h"

#include "gui/contributionreceiptdialog.h"

#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

void ContributionReceiptDialogTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void ContributionReceiptDialogTest::testShowDialog()
{
    membermanager::gui::ContributionReceiptDialog contributionDialog(1025);

    QSpinBox *spinBox = contributionDialog.findChild<QSpinBox *>("yearSpinBox");
    spinBox->setValue(2012);

    QPushButton *button = contributionDialog.findChild<QPushButton *>("showButton");
    QTest::mouseClick(button, Qt::LeftButton);

    QTextEdit *textEdit = contributionDialog.findChild<QTextEdit *>("textEdit");

    QString text = textEdit->toPlainText();

    // \todo Test ausbaucen QCOMPARE(text, QString("foo"));
}



} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::ContributionReceiptDialogTest)
#include "moc_contributionreceiptdialogtest.cpp"
