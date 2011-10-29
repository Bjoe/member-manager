#include "gui/saldodialog.h"

namespace membermanager
{
namespace gui
{

SaldoDialog::SaldoDialog(QWidget *parent)
    : QDialog(parent), saldoModel(), ui()
{
    ui.setupUi(this);
    saldoModel.initTableView(ui.saldoTableView);
    ui.saldoTableView->resizeColumnsToContents();

    float sum = saldoModel.amount();
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

void membermanager::gui::SaldoDialog::showSaldo(int anId)
{
    if (anId > 0) {
        saldoModel.setMemberId(anId);
        saldoModel.refresh();
        show();
        exec();
    }

}
