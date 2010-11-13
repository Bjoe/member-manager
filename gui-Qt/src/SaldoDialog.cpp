#include "SaldoDialog.h"
#include "DatabaseStructure.h"

namespace ClubFrontend
{

SaldoDialog::SaldoDialog(SaldoModel& aSaldoModel, QWidget *parent)
    : QDialog(parent), saldoModel(aSaldoModel), ui()
{
    ui.setupUi(this);
    ui.saldoTableView->setModel(saldoModel.getSaldoTableModel());
    ui.saldoTableView->sortByColumn(SaldoTable::saldo_pkey, Qt::DescendingOrder);
    
    ui.saldoTableView->setColumnHidden(SaldoTable::saldo_pkey, true);
    ui.saldoTableView->setColumnHidden(SaldoTable::dorfmitglied_pkey, true);
    ui.saldoTableView->resizeColumnsToContents();
    
    float sum = saldoModel.amount();
    QString sumDisplay = QString(tr("Summe: %1")).arg(sum);
    ui.sumLabel->setText(sumDisplay);
    if(sum < 0)
    {
	ui.sumLabel->setStyleSheet("QLabel { color: red }");
    }
}

SaldoDialog::~SaldoDialog()
{
}

}
