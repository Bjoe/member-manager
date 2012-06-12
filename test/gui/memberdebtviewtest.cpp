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

    QSKIP("Test muss angepasst werden.", SkipAll);
    QCOMPARE(textEdit->toPlainText(), QString(""));
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::MemberDebtViewTest)
#include "memberdebtviewtest.moc"
