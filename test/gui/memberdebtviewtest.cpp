#include "memberdebtviewtest.h"

#include <QTextEdit>
#include <QPushButton>
#include <QString>

#include "gui/memberdebtview.h"

#include "testconfig.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

void MemberDebtViewTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberDebtViewTest::testCalculate()
{
    membermanager::gui::MemberDebtView memberDebtView;

    QTextEdit *textEdit = memberDebtView.findChild<QTextEdit *>("textEdit");
    QPushButton *pushButton = memberDebtView.findChild<QPushButton *>("pushButton");

    QCOMPARE(textEdit->toPlainText(), QString(""));
    QTest::mouseClick(pushButton, Qt::LeftButton);

/*    QCOMPARE(textEdit->toPlainText(), QString("\n\nTo: fooo@baaar.xx\n\nSubject: Chaosdorf Mitgliedsbeitrag Kontostand\n\n"
                                              "Hallo James T,\n\nleider weist dein Mitgliedskontostand ein Sollwert von -10,00 EUR auf.\n"
                                              "Bitte zahle uns den ausstehenden Beitrag von 10,00 EUR auf\n"
                                              "folgendes Vereins Konto ein:\n"
                                              "Name: Chaosdorf e.V.\n"
                                              "Konto Nr.: 21057476\n"
                                              "BLZ: 300 501 10\n"
                                              "Bank: Stadtsparkasse Duesseldorf\n\n"
                                              "Als Referenz bitte folgendes Eintragen:\n"
                                              "1025 James T Kirk ausstehenden Mitgliedsbeitraege\n\n"
                                              "Sollte es Probleme oder Fragen geben, dann wende dich bitte\n"
                                              "schnellstmoeglich an den Chaosdorf Vorstand\n"
                                              "Chaosdorf Vorstand \n\n"
                                              "Diese Email wurde automatisch generiert und verschickt\n\n\n\n\n"
                                              "Gesamt Saldo: -10\n"));
*/}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::MemberDebtViewTest)
#include "moc_memberdebtviewtest.cpp"
