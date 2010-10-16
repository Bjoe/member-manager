#include "SaldoDialog.h"

namespace ClubFrontend
{

SaldoDialog::SaldoDialog(SaldoModel& aSaldoModel, QWidget *parent)
    : QDialog(parent), saldoModel(aSaldoModel), ui()
{
    ui.setupUi(this);
    ui.saldoTableView->setModel(saldoModel.getSaldoTableModel());

}

SaldoDialog::~SaldoDialog()
{
}

}
