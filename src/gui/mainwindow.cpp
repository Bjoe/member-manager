#include "gui/mainwindow.h"

#include "gui/memberdetailview.h"
#include "gui/memberdebtview.h"
#include "gui/summaryview.h"
#include "gui/paymentview.h"
#include "accounting/accountingentryimportermain.h"
#include "gui/settingsdialog.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(), listWidget(0), stackedLayout(0)
{
    ui.setupUi(this);

    listWidget = new QListWidget();
    listWidget->addItem(tr("Gesamt Ueberblick"));
    listWidget->addItem(tr("Mitglieder"));
    listWidget->addItem(tr("geloeschte Mitglieder"));
    listWidget->addItem(tr("Mitglieder Schulden"));
    listWidget->addItem(tr("Monats Buchung"));
    listWidget->addItem(tr("Buchungen Importieren"));

    stackedLayout = new QStackedWidget();
    stackedLayout->addWidget(new SummaryView(this));
    stackedLayout->addWidget(new MemberDetailView(false, this));
    stackedLayout->addWidget(new MemberDetailView(true, this));
    stackedLayout->addWidget(new MemberDebtView(this));
    stackedLayout->addWidget(new PaymentView(this));
    stackedLayout->addWidget(new accounting::AccountingEntryImporterMain(this));

    ui.horizontalLayout->addWidget(listWidget);
    ui.horizontalLayout->addWidget(stackedLayout, 1);

    connect(listWidget, SIGNAL(currentRowChanged(int)),
            stackedLayout, SLOT(setCurrentIndex(int)));

    listWidget->setCurrentRow(0);

    connect(ui.actionSettings, SIGNAL(triggered()), SLOT(showSettingsDialog()));
}

void MainWindow::showSettingsDialog()
{
    SettingsDialog settingsDialog;
    settingsDialog.exec();
}

}
}
