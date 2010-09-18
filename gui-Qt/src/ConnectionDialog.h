#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtGui/QDialog>
#include "ui_ConnectionDialog.h"

namespace ClubFrontend
{

class ConnectionDialog: public QDialog
{
Q_OBJECT

public:
	ConnectionDialog(QWidget *parent = 0);
	~ConnectionDialog();

	QString getUsername() const;
	QString getPassword() const;
	QString getDatabaseName() const;
	QString getHostname() const;
	QString getDriver() const;

	int getPort() const;

private:
	Ui::ConnectionDialogClass ui;
};

}

#endif // CONNECTIONDIALOG_H
