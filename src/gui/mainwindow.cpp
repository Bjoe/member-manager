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

    connect(ui.actionShowMember, SIGNAL(triggered()),
            SLOT(showMemberView()));
    connect(ui.actionShowDeletedMember, SIGNAL(triggered()),
            SLOT(showDeletedMemberView()));
    connect(ui.actionNewMember, SIGNAL(triggered()),
            SLOT(newMember()));
    connect(ui.actionShowSaldo, SIGNAL(triggered()),
            SLOT(showSaldo()));

//    connect ( ui.tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
//            SLOT(updateMemberMapper()));
    connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            SLOT(updateMemberMapper(QItemSelection, QItemSelection)));
}

void MainWindow::newMember()
{
    // \todo Refactor to MemberMapper
    memberMapper.newMember();
}

void MainWindow::updateMemberMapper(const QItemSelection &aSelected, const QItemSelection &aDeselected)
{
    int id = getSelection();
    // \todo if id == 0 clear memberMapper
    memberMapper.map(id);
}

void MainWindow::showSaldo()
{
    int id = getSelection();
    if(id > 0) {
        // \todo Refactor: SaldoModel in SaldoDialog!
        Model::SaldoModel model(QSqlDatabase::database(), id);
        SaldoDialog dialog(model, this);
        dialog.show();
        dialog.exec();
    }
}

int MainWindow::getSelection() const
{
    QItemSelectionModel *selectionModel = ui.tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();
    int id = 0;
    if(indexes.size() > 0) {
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
    if(selectionModel) {
        selectionModel->clearSelection();
    }

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
