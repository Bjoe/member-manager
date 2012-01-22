#include "gui/memberdetailview.h"
#include "membercontribution.h"
#include "gui/saldodialog.h"
#include "gui/contributiondialog.h"

#include "model/saldomodel.h"
#include "model/contributionmodel.h"

namespace membermanager
{
namespace gui
{

MemberDetailView::MemberDetailView(const Ui::MainWindow *anUi, QWidget *aParent) :
    QWidget(aParent), newContribution(false), member(), ui(anUi)
{
}

void MemberDetailView::showMember(Member aMember)
{
    member = aMember;

    ui->memberId->setText(QString::number(member.getMemberId()));
    ui->firstName->setText(member.getFirstname());
    ui->memberName->setText(member.getName());
    ui->nickname->setText(member.getNickname());
    ui->reference->setText(member.getReference());
    ui->email->setText(member.getEmail());
    ui->entryDate->setDate(member.getEntryDate());
    ui->info->setPlainText(member.getInfo());
    ui->city->setText(member.getCity());
    ui->street->setText(member.getStreet());
    ui->zipcode->setText(member.getZipCode());
    ui->collection->setChecked(member.isCollection());
    ui->bankName->setText(member.getBankName());
    ui->code->setText(member.getCode());
    ui->account->setText(member.getAccountNr());
    ui->deleted->setChecked(member.isDeleted());

    MemberContribution memberContribution = member.getMemberContribution();
    ui->fee->setText(QString::number(memberContribution.getFee()));
    ui->donation->setText(QString::number(memberContribution.getDonation()));
    ui->contributionInfo->setText(memberContribution.getInfo());
    ui->validFrom->setDate(memberContribution.getValidFrom());
}

void MemberDetailView::newFee()
{
    ui->fee->clear();
    ui->fee->setText(QString("15"));
    ui->donation->clear();
    ui->donation->setText(QString("0"));
    ui->contributionInfo->clear();
    ui->contributionInfo->setText(QString("Beitragsänderung"));
    ui->validFrom->setDate(QDate::currentDate());

    newContribution = true;
}

void MemberDetailView::saveMember()
{
    member.setFirstname(ui->firstName->text());
    member.setName(ui->memberName->text());
    member.setNickname(ui->nickname->text());
    member.setReference(ui->reference->text());
    member.setEmail(ui->email->text());
    member.setEntryDate(ui->entryDate->date());
    member.setInfo(ui->info->toPlainText());
    member.setCity(ui->city->text());
    member.setStreet(ui->street->text());
    member.setZipCode(ui->zipcode->text());
    member.setCollection(ui->collection->isChecked());
    member.setBankName(ui->bankName->text());
    member.setCode(ui->code->text());
    member.setAccountNr(ui->account->text());
    member.setDeleted(ui->deleted->isChecked());

    MemberContribution memberContribution = member.getMemberContribution();
    memberContribution.setFee(ui->fee->text().toDouble());
    memberContribution.setDonation(ui->donation->text().toDouble());
    memberContribution.setInfo(ui->contributionInfo->text());
    memberContribution.setValidFrom(ui->validFrom->date());

    member.save();
    if (newContribution)
        memberContribution.saveNewRecord();
    else
        memberContribution.save();

    newContribution = false;
}

void MemberDetailView::showSaldoDialog()
{
    SaldoDialog dialog(member.getSaldoModel(), this);
    dialog.exec();
}


void MemberDetailView::showContributionDialog()
{
    ContributionDialog dialog(member.getContributionModel(), this);
    dialog.exec();
}

}
}

