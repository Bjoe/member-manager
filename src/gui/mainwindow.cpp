#include "gui/mainwindow.h"

#include <QFileDialog>

#include "gui/memberdebtview.h"
#include "gui/summaryview.h"
#include "gui/paymentview.h"
#include "gui/settingsdialog.h"
#include "gui/connectiondialog.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(),
    listWidget(new QListWidget()),
    stackedLayout(new QStackedWidget()),
    memberDetailView(new MemberDetailView(false, this)),
    deletedMemberView(new MemberDetailView(true, this)),
    accountingEntryImporterView(new AccountingEntryImporterView(this))
{
    ui.setupUi(this);
    stackedLayout->setObjectName("stackedLayout");


    listWidget->addItem(tr("Gesamt Ueberblick"));
    listWidget->addItem(tr("Mitglieder"));
    listWidget->addItem(tr("geloeschte Mitglieder"));
    listWidget->addItem(tr("Mitglieder Schulden"));
    listWidget->addItem(tr("Monats Buchung"));
    listWidget->addItem(tr("Buchungen Importieren"));

    stackedLayout->addWidget(new SummaryView(this));
    stackedLayout->addWidget(memberDetailView);
    stackedLayout->addWidget(deletedMemberView);
    stackedLayout->addWidget(new MemberDebtView(this));
    stackedLayout->addWidget(new PaymentView(this));
    stackedLayout->addWidget(accountingEntryImporterView);

    ui.horizontalLayout->addWidget(listWidget);
    ui.horizontalLayout->addWidget(stackedLayout, 1);

    connect(listWidget, SIGNAL(currentRowChanged(int)),
            stackedLayout, SLOT(setCurrentIndex(int)));

    listWidget->setCurrentRow(0);

    connect(ui.actionSettings, SIGNAL(triggered()), SLOT(showSettingsDialog()));
    connect(ui.actionOpenDb, SIGNAL(triggered()), SLOT(showDatabaseDialog()));
    connect(ui.actionOpenFile, SIGNAL(triggered()), SLOT(showOpenFileDialog()));
}

void MainWindow::loadDatabase()
{
    int index = stackedLayout->indexOf(memberDetailView);
    stackedLayout->removeWidget(memberDetailView);
    delete memberDetailView;
    memberDetailView = new MemberDetailView(false, this);
    stackedLayout->insertWidget(index, memberDetailView);

    index = stackedLayout->indexOf(deletedMemberView);
    stackedLayout->removeWidget(deletedMemberView);
    delete deletedMemberView;
    deletedMemberView = new MemberDetailView(true, this);
    stackedLayout->insertWidget(index, deletedMemberView);

    index = stackedLayout->indexOf(accountingEntryImporterView);
    stackedLayout->removeWidget(accountingEntryImporterView);
    delete accountingEntryImporterView;
    accountingEntryImporterView = new AccountingEntryImporterView(this);
    stackedLayout->insertWidget(index, accountingEntryImporterView);

    listWidget->setCurrentRow(0);
}

void MainWindow::showSettingsDialog()
{
    SettingsDialog settingsDialog;
    settingsDialog.exec();
}

void MainWindow::showDatabaseDialog()
{
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

    membermanager::gui::ConnectionDialog dialog;
    dialog.setDriver(driver.toString());
    dialog.setDatabaseName(databasename.toString());
    dialog.setUsername(username.toString());
    dialog.setHostname(hostname.toString());
    dialog.setPort(port.toInt());
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(dialog.getDriver());
    db.setDatabaseName(dialog.getDatabaseName());
    db.setHostName(dialog.getHostname());
    db.setPort(dialog.getPort());
    db.setPassword(dialog.getPassword());
    db.setUserName(dialog.getUsername());
    if (!db.open()) {
        QSqlError err = db.lastError();
        if (err.type() != QSqlError::NoError) {
            QMessageBox::warning(0, QObject::tr("Unable to open database"),
                                 QObject::tr(
                                     "An error occured while opening the connection: ")
                                 + err.text());
            return;
        }
    }
    settings.setValue(driverKey, dialog.getDriver());
    settings.setValue(databaseKey, dialog.getDatabaseName());
    settings.setValue(usernameKey, dialog.getUsername());
    settings.setValue(hostnameKey, dialog.getHostname());
    settings.setValue(portKey, dialog.getPort());

    loadDatabase();
}

void MainWindow::showOpenFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open SQLite database"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if (!db.open()) {
        QSqlError err = db.lastError();
        if (err.type() != QSqlError::NoError) {
            QMessageBox::warning(0, QObject::tr("Unable to open database"),
                                 QObject::tr(
                                     "An error occured while opening the connection: ")
                                 + err.text());
            return;
        }
    }

    loadDatabase();
}

}
}
