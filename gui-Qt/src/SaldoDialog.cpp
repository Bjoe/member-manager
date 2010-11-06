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

}

SaldoDialog::~SaldoDialog()
{
}

}
