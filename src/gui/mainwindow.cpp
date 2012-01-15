#include "gui/mainwindow.h"

#include "memberfactory.h"
#include "model/memberfilter.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(const QSqlDatabase &aDatabase,
                       QWidget *parent) :
    QMainWindow(parent), ui(), memberModel(this, aDatabase), memberDetailView(&ui, this), showDeleted(false)
{
    ui.setupUi(this);

    ui.tableView->setModel(memberModel.getModel());

    showMembers();

    connect(ui.saldoButton, SIGNAL(clicked()), &memberDetailView, SLOT(showSaldoDialog()));
    connect(ui.feeButton, SIGNAL(clicked()), &memberDetailView, SLOT(showContributionDialog()));
    connect(ui.newFeeButton, SIGNAL(clicked()), &memberDetailView, SLOT(newFee()));

    connect(ui.buttonBox, SIGNAL(accepted()), SLOT(saveMember()));
    connect(ui.actionShowMember, SIGNAL(triggered()), SLOT(showMemberView()));
    connect(ui.actionShowDeletedMember, SIGNAL(triggered()), SLOT(showDeletedMemberView()));
    connect(ui.actionNewMember, SIGNAL(triggered()), SLOT(newMember()));
    //connect(ui.actionShowSaldo, SIGNAL(triggered()), SLOT(showSaldo()));
   connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            SLOT(updateMemberDetailView(QItemSelection, QItemSelection)));
}

void MainWindow::newMember()
{
    ui.tableView->selectionModel()->clearSelection();
    memberDetailView.showMember(MemberFactory::createNewMember());
}

void MainWindow::saveMember()
{
    QModelIndex index = ui.tableView->currentIndex();
    memberDetailView.saveMember();
    updateTableView();
    ui.tableView->selectRow(index.row());
}

void MainWindow::updateMemberDetailView(const QItemSelection &aSelected, const QItemSelection &aDeselected)
{
    QModelIndexList indexList = aSelected.indexes();
    int id = 0;
    if (indexList.size() > 0) {
        QModelIndex index = indexList.first();
        id = memberModel.getMemberId(index.row());
    }
    Member member = MemberFactory::createMember(id);
    memberDetailView.showMember(member);
}


void MainWindow::showDeletedMemberView()
{
    showDeleted = true;
    showMembers();
}

void MainWindow::showMemberView()
{
    showDeleted = false;
    showMembers();
}

void MainWindow::showMembers(int aRow)
{
    updateTableView();

    ui.tableView->addAction(ui.actionCopyMailAdr);
    ui.tableView->addAction(ui.actionShowSaldo);

    if (showDeleted == true) {
        ui.actionShowDeletedMember->setChecked(true);
        ui.actionShowMember->setChecked(false);
    } else {
        ui.actionShowDeletedMember->setChecked(false);
        ui.actionShowMember->setChecked(true);
    }
    ui.tableView->selectRow(aRow);
    int id = memberModel.getMemberId(aRow);
    Member member = MemberFactory::createMember(id);
    memberDetailView.showMember(member);
}

void MainWindow::updateTableView()
{
    memberModel.setFilter(model::MemberFilter::build().withDeleted(showDeleted).createFilter());
    ui.tableView->resizeColumnsToContents();
}

}
}
