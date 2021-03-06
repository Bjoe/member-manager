#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QObject>
#include <QString>
#include <QWidget>
#include <QDialog>
#include "ui_connectiondialog.h"

namespace membermanager
{
namespace gui
{

class ConnectionDialog: public QDialog
{
    Q_OBJECT

public:
    ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

    QString getUsername() const;
    void setUsername(const QString &aName);
    QString getPassword() const;
    QString getDatabaseName() const;
    void setDatabaseName(const QString &aName);
    QString getHostname() const;
    void setHostname(const QString &aName);
    QString getDriver() const;
    void setDriver(const QString &aName);
    int getPort() const;
    void setPort(const int &aPort);

private:
    ::Ui::ConnectionDialogClass ui;
};

}
}

#endif // CONNECTIONDIALOG_H
