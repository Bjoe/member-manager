#include "gui/mainwindow.h"

#include "memberfactory.h"
#include "model/memberfilter.h"
#include "gui/saldodialog.h"
#include "gui/contributiondialog.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(const QSqlDatabase &aDatabase,
                       QWidget *parent) :
    QMainWindow(parent), ui(), memberModel(aDatabase), memberDetailView(&ui)
{
    ui.setupUi(this);

    showMembers(false);

    connect(ui.buttonBox, SIGNAL(accepted()), &memberDetailView, SLOT(saveMember()));
    connect(ui.newFeeButton, SIGNAL(clicked()), &memberDetailView, SLOT(newFee()));
    connect(ui.actionShowMember, SIGNAL(triggered()), SLOT(showMemberView()));
    connect(ui.actionShowDeletedMember, SIGNAL(triggered()), SLOT(showDeletedMemberView()));
    connect(ui.actionNewMember, SIGNAL(triggered()), SLOT(newMember()));
    //connect(ui.actionShowSaldo, SIGNAL(triggered()), SLOT(showSaldo()));
    connect(ui.saldoButton, SIGNAL(clicked()), SLOT(showSaldoDialog()));
    connect(ui.feeButton, SIGNAL(clicked()), SLOT(showContributionDialog()));

    //    connect ( ui.tableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
    //            SLOT(updateMemberMapper()));
    connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            SLOT(updateMemberDetailView(QItemSelection, QItemSelection)));
}

void MainWindow::newMember()
{
    memberDetailView.showMember(MemberFactory::createNewMember());
}

void MainWindow::updateMemberDetailView(const QItemSelection &aSelected, const QItemSelection &aDeselected)
{
    memberDetailView.showMember(MemberFactory::createMember(getSelection()));
}

void MainWindow::showSaldoDialog()
{
    model::SaldoModel model = memberDetailView.getSaldoModel();
    SaldoDialog dialog(model, this);
    dialog.exec();
}


void MainWindow::showContributionDialog()
{
    model::ContributionModel model = memberDetailView.getContributionModel();
    ContributionDialog dialog(model, this);
    dialog.exec();
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

void MainWindow::showMembers(bool aBoolean)
{
    QItemSelectionModel *selectionModel = ui.tableView->selectionModel();
    if (selectionModel) {
        selectionModel->clearSelection();
    }

    memberModel.setFilter(model::MemberFilter::build().withDeleted(aBoolean).createFilter());
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
