#include <QtGui>

#include "MemberDialog.h"
#include "MemberModel.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// XXX nur zum Test!
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("dorfverw.dat");
	db.open();

	ClubFrontend::MemberModel dataSource(QSqlDatabase::database());
	ClubFrontend::MainWindow* mainWindow = new ClubFrontend::MainWindow(dataSource);
	mainWindow->show();

//    GuiVerwaltung::MemberDialog *dialog = new GuiVerwaltung::MemberDialog;
//    dialog->show();

	return app.exec();
}
