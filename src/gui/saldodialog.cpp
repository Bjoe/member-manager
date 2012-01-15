#include "gui/saldodialog.h"

#include "model/databasestructure.h"

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

    ui.saldoTableView->setModel(saldoModel.getModel());
    ui.saldoTableView->setColumnHidden(model::SaldoTable::saldo_pkey, true);
    ui.saldoTableView->setColumnHidden(model::SaldoTable::dorfmitglied_pkey, true);
    ui.saldoTableView->sortByColumn(model::SaldoTable::datum, Qt::DescendingOrder);
    ui.saldoTableView->resizeColumnsToContents();

    calculateSum();

    connect(ui.newRowButton, SIGNAL(clicked()), SLOT(insertRow()));
    connect(ui.deleteRowButton, SIGNAL(clicked()), SLOT(deleteRow()));
    connect(saldoModel.getModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(calculateSum()));
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

void SaldoDialog::calculateSum()
{
    double sum = saldoModel.amount();
    QString sumDisplay = QString(tr("Summe: %1")).arg(sum);
    ui.sumLabel->setText(sumDisplay);
    if (sum < 0) {
        ui.sumLabel->setStyleSheet("QLabel { color: red }");
    } else {
        ui.sumLabel->setStyleSheet("QLabel { color: black }");
    }
}


}
}
