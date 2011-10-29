#include "gui/membermapper.h"

#include "memberfactory.h"
#include "model/databasestructure.h"

namespace membermanager
{
namespace gui
{

MemberMapper::MemberMapper(const Ui::MainWindow *anUi, QObject *parent) :
    QObject(parent), member(), ui(anUi),
    memberMapper(new QDataWidgetMapper(this)),
    addressMapper(new QDataWidgetMapper(this)),
    bankMapper(new QDataWidgetMapper(this)),
    ressourcenMapper(new QDataWidgetMapper(this))
{}

void MemberMapper::initUi()
{
    connect(ui->buttonBox, SIGNAL(accepted()), memberMapper, SLOT(submit()));
    connect(ui->buttonBox, SIGNAL(accepted()), addressMapper, SLOT(submit()));
    connect(ui->buttonBox, SIGNAL(accepted()), bankMapper, SLOT(submit()));
    connect(ui->buttonBox, SIGNAL(accepted()), ressourcenMapper, SLOT(submit()));

    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(submitContribution()));
}

void MemberMapper::showMember(Member aMember)
{
    member = aMember;

    QString id;
    id.setNum(member.getMemberId());
    ui->memberId->setText(id);

    member.initMemberMapper(memberMapper);
    memberMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    memberMapper->addMapping(ui->firstName, model::MemberTable::FirstName);
    memberMapper->addMapping(ui->memberName, model::MemberTable::Name);
    memberMapper->addMapping(ui->nickname, model::MemberTable::NickName);
    memberMapper->addMapping(ui->entryDate, model::MemberTable::EntryDate);
    memberMapper->addMapping(ui->info, model::MemberTable::Info);
    memberMapper->toFirst();

    member.initAddressMapper(addressMapper);
    addressMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    addressMapper->addMapping(ui->city, model::AddressTable::Town);
    addressMapper->addMapping(ui->street, model::AddressTable::Street);
    addressMapper->addMapping(ui->zipcode, model::AddressTable::ZipCode);
    addressMapper->toFirst();

    member.initBankAccountMapper(bankMapper);
    bankMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    bankMapper->addMapping(ui->account, model::BankAccountTable::AccountNr);
    bankMapper->addMapping(ui->code, model::BankAccountTable::Code);
    bankMapper->addMapping(ui->bankName, model::BankAccountTable::BankName);
    bankMapper->toFirst();

    member.initRessourcenMapper(ressourcenMapper);
    ressourcenMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ressourcenMapper->addMapping(ui->email, model::RessourcenTable::EmailAdress);
    ressourcenMapper->toFirst();

    ui->contributionInfo->setText(member.getContributionInfo());
    ui->donation->setText(member.getDonation());
    ui->fee->setText(member.getFee());
}

void MemberMapper::submitContribution()
{
    member.submitContribution(ui->fee->text(), ui->donation->text(), ui->contributionInfo->text());
}

}
}
