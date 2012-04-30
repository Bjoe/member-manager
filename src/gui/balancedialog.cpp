#include "balancedialog.h"

#include <QString>
#include <QList>
#include <QSqlTableModel>
#include <QModelIndex>

#include "dao/databasestructure.h"

namespace membermanager
{
namespace gui
{

BalanceDialog::BalanceDialog(int aMemberId, QWidget *parent) :
    QDialog(parent), balanceDao(), ui(), memberId(aMemberId)
{
    ui.setupUi(this);
    QString title = QString(tr("Member Id: %1")).arg(memberId);
    setWindowTitle(title);

    QSqlTableModel *model = balanceDao.getModelByMemberId(memberId);
    ui.balanceTableView->setModel(model);
    ui.balanceTableView->setColumnHidden(dao::SaldoTable::saldo_pkey, true);
    ui.balanceTableView->setColumnHidden(dao::SaldoTable::dorfmitglied_pkey, true);
    ui.balanceTableView->sortByColumn(dao::SaldoTable::datum, Qt::DescendingOrder);
    ui.balanceTableView->resizeColumnsToContents();

    calculateSum();

    connect(ui.newRowButton, SIGNAL(clicked()), SLOT(insertRow()));
    connect(ui.deleteRowButton, SIGNAL(clicked()), SLOT(deleteRow()));
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(calculateSum()));
}

void BalanceDialog::insertRow()
{
    QModelIndex index = balanceDao.insertNewEmptyRowWithMemberId(memberId);
    ui.balanceTableView->setCurrentIndex(index);
    ui.balanceTableView->edit(index);
}

void BalanceDialog::deleteRow()
{
    QModelIndex index = ui.balanceTableView->currentIndex();
    balanceDao.deleteRow(index);
}

void BalanceDialog::calculateSum()
{
    double sum = 0;
    QList<accounting::BalanceEntry> balanceList = balanceDao.findByMemberId(memberId);
    accounting::BalanceEntry balanceEntry;
    foreach(balanceEntry, balanceList) {
        sum += balanceEntry.getValue();
    }

    QString sumDisplay = QString(tr("Summe: %1")).arg(sum);
    ui.sumLabel->setText(sumDisplay);
    if (sum < 0) {
        ui.sumLabel->setStyleSheet("QLabel { color: red }");
    } else {
        ui.sumLabel->setStyleSheet("QLabel { color: black }");
    }
}

} // namespace gui
} // namespace membermanager
