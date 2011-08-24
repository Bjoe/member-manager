#include "gui/membermapper.h"

#include "model/databasestructure.h"

namespace ClubFrontend
{
namespace Gui
{

MemberMapper::MemberMapper(const Ui::MainWindow *anUi, QObject *parent) :
    QObject(parent), member(), ui(anUi),
    memberMapper ( new QDataWidgetMapper ( this ) ),
    addressMapper ( new QDataWidgetMapper ( this ) ),
    bankMapper ( new QDataWidgetMapper ( this ) ),
    ressourcenMapper ( new QDataWidgetMapper ( this ) )
{}

void MemberMapper::initUi()
{
    connect ( ui->buttonBox, SIGNAL ( accepted() ), memberMapper, SLOT ( submit() ) );
    connect ( ui->buttonBox, SIGNAL ( accepted() ), addressMapper, SLOT ( submit() ) );
    connect ( ui->buttonBox, SIGNAL ( accepted() ), bankMapper, SLOT ( submit() ) );
    connect ( ui->buttonBox, SIGNAL ( accepted() ), ressourcenMapper, SLOT ( submit() ) );

    connect ( ui->buttonBox, SIGNAL ( accepted() ), SLOT ( submitContribution() ) );
}

void MemberMapper::newMember()
{
    member.createNewMember();
    showMember();
}

void MemberMapper::map(int anId)
{
    member = Member(anId);
    showMember();
}

void MemberMapper::showMember()
{
    QString id;
    id.setNum ( member.getMemberId() );
    ui->memberId->setText ( id );

    member.initMemberMapper(memberMapper);
    memberMapper->setSubmitPolicy ( QDataWidgetMapper::ManualSubmit );
    memberMapper->addMapping ( ui->firstName, Model::MemberTable::FirstName );
    memberMapper->addMapping ( ui->memberName, Model::MemberTable::Name );
    memberMapper->addMapping ( ui->nickname, Model::MemberTable::NickName );
    memberMapper->addMapping ( ui->entryDate, Model::MemberTable::EntryDate );
    memberMapper->addMapping ( ui->info, Model::MemberTable::Info );
    memberMapper->toFirst();

    member.initAddressMapper(addressMapper);
    addressMapper->setSubmitPolicy ( QDataWidgetMapper::ManualSubmit );
    addressMapper->addMapping ( ui->city, Model::AddressTable::Town );
    addressMapper->addMapping ( ui->street, Model::AddressTable::Street );
    addressMapper->addMapping ( ui->zipcode, Model::AddressTable::ZipCode );
    addressMapper->toFirst();

    member.initBankAccountMapper(bankMapper);
    bankMapper->setSubmitPolicy ( QDataWidgetMapper::ManualSubmit );
    bankMapper->addMapping ( ui->account, Model::BankAccountTable::AccountNr );
    bankMapper->addMapping ( ui->code, Model::BankAccountTable::Code );
    bankMapper->addMapping ( ui->bankName, Model::BankAccountTable::BankName );
    bankMapper->toFirst();

    member.initRessourcenMapper(ressourcenMapper);
    ressourcenMapper->setSubmitPolicy ( QDataWidgetMapper::ManualSubmit );
    ressourcenMapper->addMapping ( ui->email, Model::RessourcenTable::EmailAdress );
    ressourcenMapper->toFirst();

    ui->contributionInfo->setText ( member.getContributionInfo() );
    ui->donation->setText ( member.getDonation() );
    ui->fee->setText ( member.getFee() );
}

void MemberMapper::submitContribution()
{
    member.submitContribution( ui->fee->text(), ui->donation->text(), ui->contributionInfo->text() );
}

}
}
