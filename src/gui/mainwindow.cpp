#include "gui/mainwindow.h"

#include "memberfactory.h"
#include "model/memberfilter.h"
#include "gui/saldodialog.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(const QSqlDatabase &aDatabase,
                       QWidget *parent) :
    QMainWindow(parent), ui(), memberModel(aDatabase), memberMapper(&ui)
{
    ui.setupUi(this);
    memberMapper.initUi();

    showMembers(false);

    connect(ui.actionShowMember, SIGNAL(triggered()),
            SLOT(showMemberView()));
    connect(ui.actionShowDeletedMember, SIGNAL(triggered()),
            SLOT(showDeletedMemberView()));
    connect(ui.actionNewMember, SIGNAL(triggered()),
            SLOT(newMember()));
    connect(ui.actionShowSaldo, SIGNAL(triggered()),
            SLOT(showSaldo()));
    connect(ui.saldoButton, SIGNAL(clicked()),
            SLOT(showSaldo()));

    //    connect ( ui.tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
    //            SLOT(updateMemberMapper()));
    connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            SLOT(updateMemberMapper(QItemSelection, QItemSelection)));
}

void MainWindow::newMember()
{
    memberMapper.showMember(MemberFactory::createNewMember());
}

void MainWindow::updateMemberMapper(const QItemSelection &aSelected, const QItemSelection &aDeselected)
{
    memberMapper.showMember(MemberFactory::createMember(getSelection()));
}

void MainWindow::showSaldo()
{
    SaldoDialog dialog(this);
    dialog.showSaldo(getSelection());
}

int MainWindow::getSelection() const
{
    QItemSelectionModel *selectionModel = ui.tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();
    int id = 0;
    if (indexes.size() > 0) {
        QModelIndex index = indexes.first();
        id = memberModel.getMemberId(index);
    }
    return id;
}

void MainWindow::showDeletedMemberView()
{
    showMembers(true);
}

void MainWindow::showMemberView()
{
    showMembers(false);
}

void MainWindow::showMembers(const bool aBoolean)
{
    QItemSelectionModel *selectionModel = ui.tableView->selectionModel();
    if (selectionModel) {
        selectionModel->clearSelection();
    }

    model::MemberFilter filter;
    filter.setDeleted(aBoolean);
    memberModel.setFilter(filter.getFilter());
    memberModel.initTableView(ui.tableView);
    ui.tableView->resizeColumnsToContents();

    ui.tableView->addAction(ui.actionCopyMailAdr);
    ui.tableView->addAction(ui.actionShowSaldo);

    if (aBoolean) {
        ui.actionShowDeletedMember->setChecked(true);
        ui.actionShowMember->setChecked(false);
    } else {
        ui.actionShowDeletedMember->setChecked(false);
        ui.actionShowMember->setChecked(true);
    }
}

}
}
