#include <QtGui>
#include <QtSql>

#include "Gui/ConnectionDialog.h"
#include "Gui/MemberDialog.h"
#include "Model/MemberModel.h"
#include "Model/KassaModel.h"
#include "Gui/MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setApplicationName("Dorfverwaltung");
	app.setOrganizationName("Chaosdorf");
	app.setOrganizationDomain("www.chaosdorf.de");

	const QString driverKey("connection/driver");
	const QString databaseKey("connection/database");
	const QString usernameKey("connection/user");
	const QString hostnameKey("connection/host");
	const QString portKey("connection/port");

	QSettings settings;
	QVariant driver = settings.value(driverKey);
	QVariant databasename = settings.value(databaseKey);
	QVariant username = settings.value(usernameKey);
	QVariant hostname = settings.value(hostnameKey);
	QVariant port = settings.value(portKey);

	ClubFrontend::ConnectionDialog dialog;
	dialog.setDriver(driver.toString());
	dialog.setDatabaseName(databasename.toString());
	dialog.setUsername(username.toString());
	dialog.setHostname(hostname.toString());
	dialog.setPort(port.toInt());
	if (dialog.exec() != QDialog::Accepted)
	{
		return 0;
	}

	QSqlDatabase db = QSqlDatabase::addDatabase(dialog.getDriver());
	db.setDatabaseName(dialog.getDatabaseName());
	db.setPort(dialog.getPort());
	db.setPassword(dialog.getPassword());
	db.setUserName(dialog.getUsername());
	if (!db.open())
	{
		QSqlError err = db.lastError();
		if (err.type() != QSqlError::NoError)
		{
			QMessageBox::warning(0, QObject::tr("Unable to open database"),
					QObject::tr(
							"An error occured while opening the connection: ")
							+ err.text());
			return 1;
		}
	}
	settings.setValue(driverKey, dialog.getDriver());
	settings.setValue(databaseKey, dialog.getDatabaseName());
	settings.setValue(usernameKey, dialog.getUsername());
	settings.setValue(hostnameKey, dialog.getHostname());
	settings.setValue(portKey, dialog.getPort());

	ClubFrontend::MemberModel memberModel(db);
	ClubFrontend::KassaModel kassaModel(db);
	ClubFrontend::MainWindow* mainWindow = new ClubFrontend::MainWindow(
			memberModel, kassaModel);
	mainWindow->show();

	return app.exec();
}
