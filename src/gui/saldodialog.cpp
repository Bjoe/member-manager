#include "gui/saldodialog.h"

namespace membermanager
{
namespace gui
{

SaldoDialog::SaldoDialog(model::SaldoModel *aSaldoModel, QWidget *parent)
    : QDialog(parent), saldoModel(aSaldoModel), ui()
{
    ui.setupUi(this);
    saldoModel->initTableView(ui.saldoTableView);

    ui.saldoTableView->resizeColumnsToContents();

    double sum = saldoModel->amount();
    QString sumDisplay = QString(tr("Summe: %1")).arg(sum);
    ui.sumLabel->setText(sumDisplay);
    if (sum < 0) {
        ui.sumLabel->setStyleSheet("QLabel { color: red }");
    }
}

SaldoDialog::~SaldoDialog()
{
}

}
}
