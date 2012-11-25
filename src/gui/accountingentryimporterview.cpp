#include "accountingentryimporterview.h"
#include "ui_accountingentryimporterview.h"

#include <QString>
#include <QList>
#include <QFileDialog>

#include "swift/importer.h"
#include "swift/transaction.h"

#include "gui/memberlistdelegate.h"

namespace membermanager
{
namespace gui
{

AccountingEntryImporterView::AccountingEntryImporterView(QWidget *parent) :
    QWidget(parent),
    cashAccountdao(),
    balancePersister(0),
    ui(new Ui::AccountingEntryImporterView)
{
    ui->setupUi(this);

    QTableWidget *accountingEntryTable = ui->tableWidget;
    accountingEntryTable->setColumnCount(10);

    QStringList headerStringList;
    headerStringList << tr("Mitglieds Nr")
                     << tr("Mitglied")
                     << tr("Beitrag")
                     << tr("Spende")
                     << tr("CCC")
                     << tr("Datum")
                     << tr("Betrag")
                     << tr("Transaction")
                     << tr("Name")
                     << tr("Booked");
    accountingEntryTable->setHorizontalHeaderLabels(headerStringList);
    accountingEntryTable->setItemDelegateForColumn(1, new MemberListDelegate());

    balancePersister = new accounting::BalancePersister(accountingEntryTable, this);
    cashAccountdao.clearAndAddTransaction(accountingEntryTable);

    connect(ui->bookingButton, SIGNAL(clicked()), balancePersister, SLOT(booking()));
    connect(ui->importButton, SIGNAL(clicked()), SLOT(import()));
}

AccountingEntryImporterView::~AccountingEntryImporterView()
{
    delete ui;
}

void AccountingEntryImporterView::import()
{
    QSettings settings;
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();

    qiabanking::swift::Importer importer(bankCode, accountNumber);
    QString filename = QFileDialog::getOpenFileName(this,tr("Import SWIFT MT940"));
    QList<qiabanking::swift::Transaction *> transactionList = importer.importMt940Swift(filename);
    cashAccountdao.importTransactions(transactionList);
    cashAccountdao.clearAndAddTransaction(ui->tableWidget);
}

} // namespace gui
} // namespace membermanager
