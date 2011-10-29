#include "gui/connectiondialog.h"

#include <QSqlDatabase>

namespace membermanager
{
namespace gui
{

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    QStringList drivers = QSqlDatabase::drivers();
    ui.driver->addItems(drivers);

    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

ConnectionDialog::~ConnectionDialog()
{

}

QString ConnectionDialog::getUsername() const
{
    return ui.username->text();
}

void ConnectionDialog::setUsername(const QString &aName)
{
    ui.username->setText(aName);
}

QString ConnectionDialog::getPassword() const
{
    return ui.passwd->text();
}

QString ConnectionDialog::getHostname() const
{
    return ui.hostname->text();
}

void ConnectionDialog::setHostname(const QString &aName)
{
    ui.hostname->setText(aName);
}

QString ConnectionDialog::getDatabaseName() const
{
    return ui.databaseName->text();
}

void ConnectionDialog::setDatabaseName(const QString &aName)
{
    ui.databaseName->setText(aName);
}

QString ConnectionDialog::getDriver() const
{
    return ui.driver->currentText();
}

void ConnectionDialog::setDriver(const QString &aName)
{
    const int result = ui.driver->findText(aName);
    if (result > -1)
        ui.driver->setCurrentIndex(result);
}

int ConnectionDialog::getPort() const
{
    return ui.port->value();
}

void ConnectionDialog::setPort(const int &aPort)
{
    ui.port->setValue(aPort);
}

}
}
