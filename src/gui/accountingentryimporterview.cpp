#include "accountingentryimporterview.h"
#include "ui_accountingentryimporterview.h"

#include "gui/memberlistdelegate.h"

namespace membermanager
{
namespace gui
{

AccountingEntryImporterView::AccountingEntryImporterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountingEntryImporterView)
{
    ui->setupUi(this);

    QTableWidget *accountingEntryTable = ui->tableWidget;
    accountingEntryTable->setColumnCount(9);

    QStringList headerStringList;
    headerStringList << tr("Mitglieds Nr")
                     << tr("Mitglied")
                     << tr("Beitrag")
                     << tr("Spende")
                     << tr("CCC")
                     << tr("Datum")
                     << tr("Betrag")
                     << tr("Transaction")
                     << tr("Booked");
    accountingEntryTable->setHorizontalHeaderLabels(headerStringList);
    accountingEntryTable->setItemDelegateForColumn(1, new MemberListDelegate());

    connect(ui->bookingButton, SIGNAL(clicked()), SLOT(bookClick()));
    connect(ui->importButton, SIGNAL(clicked()), SLOT(importClick()));
}

AccountingEntryImporterView::~AccountingEntryImporterView()
{
    delete ui;
}

QTableWidget *AccountingEntryImporterView::getAccountingEntryTable() const
{
    return ui->tableWidget;
}

void AccountingEntryImporterView::importClick()
{
    emit importClicked();
}

void AccountingEntryImporterView::bookClick()
{
    emit bookClicked();
}

} // namespace gui
} // namespace membermanager
