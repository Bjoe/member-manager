#include "gui/mainwindow.h"

#include "gui/summarywindow.h"
#include "cashsumsummary.h"
#include "debitsumsummary.h"
#include "model/databasestructure.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(const QSqlDatabase &aDatabase,
                       QWidget *parent) :
    QMainWindow(parent), ui(), memberDao(aDatabase, this), memberDetailView(&ui, this), memberModel(memberDao.model()), showDeleted(false)
{
    ui.setupUi(this);

    ui.tableView->setModel(memberModel);
    ui.tableView->setColumnHidden(model::MemberTable::Deleted, true);
    ui.tableView->setColumnHidden(model::MemberTable::FOO_CCC, true);
    ui.tableView->setColumnHidden(model::MemberTable::FOO_ChaosNr, true);
    ui.tableView->setColumnHidden(model::MemberTable::FOO_ClubAdress, true);
    ui.tableView->setColumnHidden(model::MemberTable::FOO_Einzug, true);
    ui.tableView->setColumnHidden(model::MemberTable::FOO_intern, true);
    ui.tableView->setColumnHidden(model::MemberTable::FOO_Shell, true);
    ui.tableView->setColumnHidden(model::MemberTable::Info, true);

    showMembers();

    connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            SLOT(updateMemberDetailView(QItemSelection, QItemSelection)));

    connect(ui.saldoButton, SIGNAL(clicked()), &memberDetailView, SLOT(showSaldoDialog()));
    connect(ui.feeButton, SIGNAL(clicked()), &memberDetailView, SLOT(showContributionDialog()));
    connect(ui.newFeeButton, SIGNAL(clicked()), &memberDetailView, SLOT(newFee()));

    connect(ui.buttonBox, SIGNAL(accepted()), SLOT(saveMember()));
    connect(ui.actionShowMember, SIGNAL(triggered()), SLOT(showMemberView()));
    connect(ui.actionShowDeletedMember, SIGNAL(triggered()), SLOT(showDeletedMemberView()));
    connect(ui.actionNewMember, SIGNAL(triggered()), SLOT(newMember()));
    connect(ui.actionSummary, SIGNAL(triggered()), SLOT(managerSummary()));
    //connect(ui.actionShowSaldo, SIGNAL(triggered()), SLOT(showSaldo()));

}

void MainWindow::newMember()
{
    ui.tableView->selectionModel()->clearSelection();
    int id = memberDao.newMember();
    memberDetailView.showMember(memberDao.findByMemberId(id));
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
    Member member;
    if (indexList.size() > 0) {
        QModelIndex index = indexList.first();
        int id = index.data().toInt();
        member = memberDao.findByMemberId(id);
    }
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

void MainWindow::showMembers()
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
    ui.tableView->selectRow(0);
    Member member = memberDao.findByRow(0);
    memberDetailView.showMember(member);
}

void MainWindow::updateTableView()
{
    QString deleted = "'false'";
    if(showDeleted) {
        deleted = "'true'";
    }

    QString columnname = model::MemberTable::COLUMNNAME[model::MemberTable::Deleted];
    QString filter = QString("%1 = %2").arg(columnname).arg(deleted);

    memberModel->setFilter(filter);
    memberModel->select();

    ui.tableView->resizeColumnsToContents();
}

void MainWindow::managerSummary()
{
    QList<Member> memberList = memberDao.findByDeleted(showDeleted);
    CashSumSummary cashSum(memberList);
    DebitSumSummary debitSum(memberList);

    SummaryWindow summaryWindow(this);
    summaryWindow.addSummary(&cashSum);
    summaryWindow.addSummary(&debitSum);
    summaryWindow.exec();
}

}
}
