#include "gui/saldodialog.h"

namespace membermanager
{
namespace gui
{

SaldoDialog::SaldoDialog(model::SaldoModel aSaldoModel, QWidget *parent)
    : QDialog(parent), saldoModel(aSaldoModel), ui()
{
    ui.setupUi(this);
    QString title = QString(tr("Member Id: %1")).arg(saldoModel.getMemberId());
    setWindowTitle(title);
    saldoModel.initTableView(ui.saldoTableView);

    ui.saldoTableView->resizeColumnsToContents();

    double sum = saldoModel.amount();
    QString sumDisplay = QString(tr("Summe: %1")).arg(sum);
    ui.sumLabel->setText(sumDisplay);
    if (sum < 0) {
        ui.sumLabel->setStyleSheet("QLabel { color: red }");
    }

    connect(ui.newRowButton, SIGNAL(clicked()), SLOT(insertRow()));
    connect(ui.deleteRowButton, SIGNAL(clicked()), SLOT(deleteRow()));
}

SaldoDialog::~SaldoDialog()
{
}

void SaldoDialog::insertRow()
{
    QModelIndex index = saldoModel.insertNewRow();
    ui.saldoTableView->setCurrentIndex(index);
    ui.saldoTableView->edit(index);
}

void SaldoDialog::deleteRow()
{
    QModelIndex index = ui.saldoTableView->currentIndex();
    saldoModel.deleteRow(index);
}

}
}
