#include "balancedialog.h"

#include <QString>
#include <QList>
#include <QHash>
#include <QClipboard>
#include <QApplication>
#include <QSqlTableModel>
#include <QModelIndex>
#include <QModelIndexList>
#include <QItemSelectionModel>

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
    ui.balanceTableView->setColumnHidden(dao::BalanceTable::saldo_pkey, true);
    ui.balanceTableView->setColumnHidden(dao::BalanceTable::dorfmitglied_pkey, true);
    ui.balanceTableView->sortByColumn(dao::BalanceTable::datum, Qt::DescendingOrder);
    ui.balanceTableView->resizeColumnsToContents();

    calculateSum();

    connect(ui.newRowButton, SIGNAL(clicked()), SLOT(insertRow()));
    connect(ui.deleteRowButton, SIGNAL(clicked()), SLOT(deleteRow()));
    connect(ui.actionCopy, SIGNAL(triggered()), SLOT(copy()));
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), SLOT(calculateSum()));

    ui.balanceTableView->addAction(ui.actionCopy);
    ui.balanceTableView->setContextMenuPolicy(Qt::ActionsContextMenu);
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

void BalanceDialog::copy()
{
    QItemSelectionModel *selectionModel = ui.balanceTableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();

    QHash<int, QString> buffer;
    QModelIndex index;
    QVariant data;
    QString string;
    int row;
    foreach(index, indexes) {
        data = index.data();
        row = index.row();
        string = buffer.value(row);
        buffer.insert(row, QString("%1%2\t").arg(string).arg(data.toString()));
    }

    QString clipboardText;
    QHash<int, QString>::const_iterator i;
    for(i = buffer.constBegin(); i != buffer.constEnd(); ++i) {
        clipboardText.append(QString("%1\n").arg(i.value()));
    }
    QApplication::clipboard()->setText(clipboardText);
}

} // namespace gui
} // namespace membermanager
