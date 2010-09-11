#include <QtGui>

#include "MemberDialog.h"
#include "DatabaseStructure.h"

namespace ClubFrontend
{

MemberDialog::MemberDialog(const int anId, QWidget *parent) :
		QWidget(parent), memberDetailModel(QSqlDatabase::database())

{
	setupUi(this);

	memberDetailModel.setMemberId(anId);
	QString id;
	id.setNum(anId);
	memberId->setText(id);

	memberMapper = new QDataWidgetMapper(this);
	memberMapper->setModel(memberDetailModel.getMemberTableModel());
	memberMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	memberMapper->addMapping(firstName, MemberTable::FirstName);
	memberMapper->addMapping(memberName, MemberTable::Name);
	memberMapper->addMapping(nickname, MemberTable::NickName);
	memberMapper->addMapping(entryDate, MemberTable::EntryDate);
	memberMapper->addMapping(info, MemberTable::Info);
	memberMapper->toFirst();

	addressMapper = new QDataWidgetMapper(this);
	addressMapper->setModel(memberDetailModel.getAddressTableModel());
	addressMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	addressMapper->addMapping(city, AddressTable::Town);;
	addressMapper->addMapping(street, AddressTable::Street);
	addressMapper->addMapping(zipcode, AddressTable::ZipCode);
	addressMapper->toFirst();

	bankMapper = new QDataWidgetMapper(this);
	bankMapper->setModel(memberDetailModel.getBankAccountTableModel());
	bankMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	bankMapper->addMapping(account, BankAccountTable::AccountNr);
	bankMapper->addMapping(code, BankAccountTable::Code);
	bankMapper->addMapping(bankName, BankAccountTable::BankName);
	bankMapper->toFirst();

	contributionMapper = new QDataWidgetMapper(this);
	contributionMapper->setModel(memberDetailModel.getContributionTableModel());
	contributionMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	contributionMapper->addMapping(contributionInfo, ContributionTable::Info);
	contributionMapper->addMapping(donation, ContributionTable::Donation);
	contributionMapper->addMapping(fee, ContributionTable::Fee);
	contributionMapper->toFirst();

	ressourcenMapper = new QDataWidgetMapper(this);
	ressourcenMapper->setModel(memberDetailModel.getRessourcenTableModel());
	ressourcenMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	ressourcenMapper->addMapping(email, RessourcenTable::EmailAdress);
	ressourcenMapper->toFirst();

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveMember()));
}

void MemberDialog::saveMember()
{
	memberMapper->submit();
	addressMapper->submit();
	contributionMapper->submit();
	bankMapper->submit();
	ressourcenMapper->submit();
}

}
