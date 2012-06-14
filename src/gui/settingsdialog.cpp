#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QVariant>

namespace membermanager
{
namespace gui
{

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    settings(),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QString account = settings.value("bank/account").toString();
    ui->accountLineEdit->setText(account);

    QString bank = settings.value("bank/name").toString();
    ui->bankLineEdit->setText(bank);

    QString code = settings.value("bank/code").toString();
    ui->codeLineEdit->setText(code);

    connect(ui->saveButton, SIGNAL(clicked()), SLOT(saveSettings()));
}

void SettingsDialog::saveSettings()
{
    QString account = ui->accountLineEdit->text();
    QString bank = ui->bankLineEdit->text();
    QString code = ui->codeLineEdit->text();

    settings.setValue("bank/account", QVariant(account));
    settings.setValue("bank/name", QVariant(bank));
    settings.setValue("bank/code", QVariant(code));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

} // namespace gui
} // namespace membermanager
