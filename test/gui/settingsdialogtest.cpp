#include "settingsdialogtest.h"

#include "gui/settingsdialog.h"

#include <QPushButton>
#include <QLineEdit>
#include <QSettings>
#include <QString>

namespace membermanagertest
{
namespace gui
{

void SettingsDialogTest::testSettings()
{
    membermanager::gui::SettingsDialog settingsDialog;

    QLineEdit *accountLineEdit = settingsDialog.findChild<QLineEdit *>("accountLineEdit");
    QLineEdit *bankLineEdit = settingsDialog.findChild<QLineEdit *>("bankLineEdit");
    QLineEdit *codeLineEdit = settingsDialog.findChild<QLineEdit *>("codeLineEdit");
    QPushButton *saveButton = settingsDialog.findChild<QPushButton *>("saveButton");

    accountLineEdit->setText("123456");
    bankLineEdit->setText("foobar");
    codeLineEdit->setText("23456798");

    QTest::mouseClick(saveButton, Qt::LeftButton);

    QSettings settings;
    QString account = settings.value("bank/account").toString();
    QCOMPARE(account, QString("123456"));
    QString bank = settings.value("bank/name").toString();
    QCOMPARE(bank, QString("foobar"));
    QString code = settings.value("bank/code").toString();
    QCOMPARE(code, QString("23456798"));
}

} // namespace gui
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::gui::SettingsDialogTest)
#include "settingsdialogtest.moc"
