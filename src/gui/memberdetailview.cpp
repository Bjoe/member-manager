#include "gui/memberdetailview.h"
#include "gui/contributiondialog.h"
#include "gui/contributionreceiptdialog.h"
#include "gui/balancedialog.h"

#include "dao/databasestructure.h"
#include "dao/contributiondao.h"
#include "dao/memberdao.h"

namespace membermanager
{
namespace gui
{

MemberDetailView::MemberDetailView(bool isDeleted, QWidget *aParent) :
    QWidget(aParent), ui(), memberDao(QSqlDatabase::database(), this), member(), memberContribution(), newContribution(false)
{
    ui.setupUi(this);

    memberDao.selectDeleted(isDeleted);
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

    connect(ui.saldoButton, SIGNAL(clicked()), SLOT(showSaldoDialog()));
    connect(ui.feeButton, SIGNAL(clicked()), SLOT(showContributionDialog()));
    connect(ui.newFeeButton, SIGNAL(clicked()), SLOT(newFee()));
    connect(ui.contributionButton, SIGNAL(clicked()), SLOT(showContributionReceiptDialog()));
    connect(ui.saveButton, SIGNAL(clicked()), SLOT(saveMember()));
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(newMember()));

    ui.tableView->selectRow(0);
    dao::MemberDao mDao(QSqlDatabase::database(), this);
    int memberId = mDao.findByRow(0).getMemberId();
    showMember(memberId);
}

void MemberDetailView::updateMemberDetailView(const QItemSelection &aSelected, const QItemSelection &aDeselected)
{
    QModelIndexList indexList = aSelected.indexes();
    int id = 0;
    if (indexList.size() > 0) {
        QModelIndex index = indexList.first();
        id = index.data().toInt();
    }
    showMember(id);
}

void MemberDetailView::showMember(int aMemberId)
{
    dao::MemberDao mDao(QSqlDatabase::database(), this);
    member = mDao.findByMemberId(aMemberId);

    ui.memberId->setText(QString::number(aMemberId));
    ui.firstName->setText(member.getFirstname());
    ui.memberName->setText(member.getName());
    ui.nickname->setText(member.getNickname());
    ui.reference->setText(member.getReference());
    ui.email->setText(member.getEmail());
    ui.entryDate->setDate(member.getEntryDate());
    ui.info->setPlainText(member.getInfo());
    ui.city->setText(member.getCity());
    ui.street->setText(member.getStreet());
    ui.zipcode->setText(member.getZipCode());
    ui.collection->setChecked(member.isCollection());
    ui.bankName->setText(member.getBankName());
    ui.code->setText(member.getCode());
    ui.account->setText(member.getAccountNr());
    ui.deleted->setChecked(member.isDeleted());

    dao::ContributionDao contributionDao(QSqlDatabase::database());
    memberContribution = contributionDao.findLastDateByMemberId(aMemberId);
    ui.fee->setText(QString::number(memberContribution.getFee()));
    ui.donation->setText(QString::number(memberContribution.getDonation()));
    ui.contributionInfo->setText(memberContribution.getInfo());
    ui.validFrom->setDate(memberContribution.getValidFrom());
}

void MemberDetailView::newFee()
{
    ui.fee->clear();
    ui.fee->setText(QString("15"));
    ui.donation->clear();
    ui.donation->setText(QString("0"));
    ui.contributionInfo->clear();
    ui.contributionInfo->setText(QString("Beitragsänderung"));
    ui.validFrom->setDate(QDate::currentDate());

    int memberId = member.getMemberId();
    memberContribution = accounting::ContributionEntry(memberId);
}

void MemberDetailView::newMember()
{
    ui.tableView->selectionModel()->clearSelection();
    int id = memberDao.newMember();
    showMember(id);
    memberDao.model()->select();
}

void MemberDetailView::saveMember()
{
    QModelIndex index = ui.tableView->currentIndex();

    member.setFirstname(ui.firstName->text());
    member.setName(ui.memberName->text());
    member.setNickname(ui.nickname->text());
    member.setReference(ui.reference->text());
    member.setEmail(ui.email->text());
    member.setEntryDate(ui.entryDate->date());
    member.setInfo(ui.info->toPlainText());
    member.setCity(ui.city->text());
    member.setStreet(ui.street->text());
    member.setZipCode(ui.zipcode->text());
    member.setCollection(ui.collection->isChecked());
    member.setBankName(ui.bankName->text());
    member.setCode(ui.code->text());
    member.setAccountNr(ui.account->text());
    member.setDeleted(ui.deleted->isChecked());

    memberContribution.setFee(ui.fee->text().toDouble());
    memberContribution.setDonation(ui.donation->text().toDouble());
    memberContribution.setInfo(ui.contributionInfo->text());
    memberContribution.setValidFrom(ui.validFrom->date());

    dao::MemberDao mDao(QSqlDatabase::database(), this);
    mDao.saveRecord(member);

    dao::ContributionDao contributionDao(QSqlDatabase::database(), this);
    contributionDao.saveRecord(memberContribution);

    memberDao.model()->select();
    ui.tableView->resizeColumnsToContents();
    ui.tableView->selectRow(index.row());
}

void MemberDetailView::showSaldoDialog()
{
    int memberId = member.getMemberId();
    BalanceDialog dialog(memberId, this);
    dialog.exec();
}

void MemberDetailView::showContributionDialog()
{
    int memberId = member.getMemberId();
    ContributionDialog dialog(memberId, this);
    dialog.exec();
}

void MemberDetailView::showContributionReceiptDialog()
{
    int memberId = member.getMemberId();
    ContributionReceiptDialog dialog(memberId, this);
    dialog.exec();
}

}
}
