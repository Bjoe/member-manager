#include "gui/mainwindow.h"

#include "model/memberfilter.h"
#include "gui/saldodialog.h"

namespace ClubFrontend
{
namespace Gui
{

MainWindow::MainWindow(const QSqlDatabase &aDatabase,
                       QWidget *parent) :
    QMainWindow(parent), ui(), memberModel(aDatabase), memberMapper(&ui)
{
    ui.setupUi(this);
    memberMapper.initUi();

    showMembers(false);

    connect(ui.actionShowDeletedMember, SIGNAL(triggered()),
            SLOT(showDeletedMemberView()));
    connect(ui.actionNewMember, SIGNAL(triggered()),
            SLOT(newMember()));
    connect(ui.actionShowSaldo, SIGNAL(triggered()),
            SLOT(showSaldo()));

//    connect ( ui.tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
//            SLOT(updateMemberMapper()));
    connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            SLOT(updateMemberMapper()));
}

void MainWindow::newMember()
{
    // \todo Refactor to MemberMapper
    memberMapper.newMember();
}

void MainWindow::updateMemberMapper()
{
    int id = getSelection();
    memberMapper.map(id);
}

void MainWindow::showSaldo()
{
    int id = getSelection();

    // \todo Refactor: SaldoModel in SaldoDialog!
    Model::SaldoModel model(QSqlDatabase::database(), id);
    SaldoDialog dialog(model, this);
    dialog.show();
    dialog.exec();
}

int MainWindow::getSelection() const
{
    QItemSelectionModel *selectionModel = ui.tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();
    QModelIndex index = indexes.first();
    return memberModel.getMemberId(index);
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
    Model::MemberFilter filter;
    filter.setDeleted(aBoolean);
    memberModel.setFilter(filter.getFilter());
    memberModel.initTableView(ui.tableView);
    ui.tableView->resizeColumnsToContents();

    ui.tableView->addAction(ui.actionCopyMailAdr);
    ui.tableView->addAction(ui.actionShowSaldo);

    if(aBoolean) {
        ui.actionShowDeletedMember->setChecked(true);
        ui.actionShowMember->setChecked(false);
    } else {
        ui.actionShowDeletedMember->setChecked(false);
        ui.actionShowMember->setChecked(true);
    }
}

}
}
