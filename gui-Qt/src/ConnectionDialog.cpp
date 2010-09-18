#include "ConnectionDialog.h"

#include <QSqlDatabase>

namespace ClubFrontend
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

QString ConnectionDialog::getPassword() const
{
	return ui.passwd->text();
}

QString ConnectionDialog::getHostname() const
{
	return ui.hostname->text();
}

QString ConnectionDialog::getDatabaseName() const
{
	return ui.databaseName->text();
}

QString ConnectionDialog::getDriver() const
{
	return ui.driver->currentText();
}

int ConnectionDialog::getPort() const
{
	return ui.port->value();
}

}
