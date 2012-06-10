#include "gui/mainwindow.h"

#include "gui/summarywindow.h"
#include "cashsumsummary.h"
#include "debitsumsummary.h"
#include "dao/databasestructure.h"
#include "accounting/pay.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(const QSqlDatabase &aDatabase,
                       QWidget *parent) :
    QMainWindow(parent), ui(), memberDao(aDatabase, this), memberDetailView(&ui, this), showDeleted(false)
{
    ui.setupUi(this);

    ui.tableView->setModel(memberDao.model());
    ui.tableView->setColumnHidden(dao::MemberTable::Deleted, true);
    ui.tableView->setColumnHidden(dao::MemberTable::FOO_CCC, true);
    ui.tableView->setColumnHidden(dao::MemberTable::FOO_ChaosNr, true);
    ui.tableView->setColumnHidden(dao::MemberTable::FOO_ClubAdress, true);
    ui.tableView->setColumnHidden(dao::MemberTable::FOO_Einzug, true);
    ui.tableView->setColumnHidden(dao::MemberTable::FOO_intern, true);
    ui.tableView->setColumnHidden(dao::MemberTable::FOO_Shell, true);
    ui.tableView->setColumnHidden(dao::MemberTable::Info, true);

    connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            SLOT(updateMemberDetailView(QItemSelection, QItemSelection)));

    connect(ui.saldoButton, SIGNAL(clicked()), &memberDetailView, SLOT(showSaldoDialog()));
    connect(ui.feeButton, SIGNAL(clicked()), &memberDetailView, SLOT(showContributionDialog()));
    connect(ui.newFeeButton, SIGNAL(clicked()), &memberDetailView, SLOT(newFee()));
    connect(ui.contributionButton, SIGNAL(clicked()), &memberDetailView, SLOT(showContributionReceiptDialog()));

    connect(ui.buttonBox, SIGNAL(accepted()), SLOT(saveMember()));
    connect(ui.actionShowMember, SIGNAL(triggered()), SLOT(showMemberView()));
    connect(ui.actionShowDeletedMember, SIGNAL(triggered()), SLOT(showDeletedMemberView()));
    connect(ui.actionNewMember, SIGNAL(triggered()), SLOT(newMember()));
    connect(ui.actionSummary, SIGNAL(triggered()), SLOT(managerSummary()));
    connect(ui.actionMemberCollectionWithBooking, SIGNAL(triggered()), SLOT(memberCollectionWithBooking()));
    connect(ui.actionMemberCollectionWithoutBooking, SIGNAL(triggered()), SLOT(memberCollectionWithoutBooking()));
    //connect(ui.actionShowSaldo, SIGNAL(triggered()), SLOT(showSaldo()));

    showMembers();
}

void MainWindow::newMember()
{
    ui.tableView->selectionModel()->clearSelection();
    int id = memberDao.newMember();
    memberDetailView.showMember(id);
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
        id = index.data().toInt();
    }
    memberDetailView.showMember(id);
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
    memberDetailView.showMember(member.getMemberId());
}

void MainWindow::updateTableView()
{
    memberDao.selectDeleted(showDeleted);
    ui.tableView->resizeColumnsToContents();
}

void MainWindow::managerSummary()
{
    dao::MemberDao dao;
    QList<Member> memberList = dao.findByDeleted(showDeleted);
    CashSumSummary cashSum(memberList);
    DebitSumSummary debitSum(memberList);

    SummaryWindow summaryWindow(this);
    summaryWindow.addSummary(&cashSum);
    summaryWindow.addSummary(&debitSum);
    summaryWindow.exec();
}

void MainWindow::memberCollectionWithBooking()
{
    memberCollection(true);
}

void MainWindow::memberCollectionWithoutBooking()
{
    memberCollection(false);
}

void MainWindow::memberCollection(bool isBooking)
{
    QDate date = QDate::currentDate();

    QSettings settings;
    QString bankName = settings.value("bank/name").toString();
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();

    membermanager::accounting::Pay pay(accountNumber, bankName, bankCode);

    dao::MemberDao dao;
    QList<Member> memberList = dao.findByDeleted(false);
    foreach(const Member member, memberList) {
       pay.payment(member, date.toString("MMM"), date, isBooking);
    }

    QString filename = QString("DTAUS_%1.txt").arg(date.toString(Qt::ISODate));
    QList<double> sum = pay.balancing("DTAUS0.txt");

    filename = QString("sum-%1.csv").arg(date.toString(Qt::ISODate));
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << date.toString("dd.MM.yyyy") << ";" << "Einzug 011" << ";" << "011 Mitgliedsbeitraege" << ";" << sum[0] << "\n";
    out << date.toString("dd.MM.yyyy") << ";" << "Einzug 012" << ";" << "012 Spenden" << ";" << sum[1] << "\n";
    file.close();
}

}
}
