#include <QtGui>
#include <QtSql>

#include "ConnectionDialog.h"
#include "MemberDialog.h"
#include "MemberModel.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	ClubFrontend::ConnectionDialog dialog;
	if(dialog.exec() != QDialog::Accepted) {
		return 0;
	}

	QSqlDatabase db = QSqlDatabase::addDatabase(dialog.getDriver());
	db.setDatabaseName(dialog.getDatabaseName());
	db.setPort(dialog.getPort());
	db.setPassword(dialog.getPassword());
	db.setUserName(dialog.getUsername());
	if(!db.open()) {
		QSqlError err = db.lastError();
		if(err.type() != QSqlError::NoError) {
			QMessageBox::warning(0, QObject::tr("Unable to open database"),
					QObject::tr("An error occured while opening the connection: ") + err.text());
			return 1;
		}
	}

	ClubFrontend::MemberModel dataSource(db);
	ClubFrontend::MainWindow* mainWindow = new ClubFrontend::MainWindow(dataSource);
	mainWindow->show();

	return app.exec();
}
