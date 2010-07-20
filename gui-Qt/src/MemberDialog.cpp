#include <QtGui>

#include "MemberDialog.h"

namespace ClubFrontend
{

MemberDialog::MemberDialog(QWidget *parent) :
		QWidget(parent), memberDetailModel(QSqlDatabase::database())

{
	setupUi(this);
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveMember()));
}

void MemberDialog::showMember()
{
	QDataWidgetMapper* memberMapper = new QDataWidgetMapper(this);
	memberMapper->setModel(memberDetailModel.getMemberTableModel());
	memberMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	memberMapper->addMapping(firstName, 2);
	memberMapper->addMapping(memberName, 3);
	memberMapper->addMapping(nickname, 4);
	memberMapper->addMapping(entryDate, 11);
	memberMapper->addMapping(info, 12);
	memberMapper->toFirst();

	QDataWidgetMapper* addressMapper = new QDataWidgetMapper(this);
	addressMapper->setModel(memberDetailModel.getAddressTableModel());
	addressMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	addressMapper->addMapping(city, 4);;
	addressMapper->addMapping(street, 2);
	addressMapper->addMapping(zipcode, 3);
	addressMapper->toFirst();

	QDataWidgetMapper* bankMapper = new QDataWidgetMapper(this);
	bankMapper->setModel(memberDetailModel.getBankAccountTableModel());
	bankMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	bankMapper->addMapping(account, 2);
	bankMapper->addMapping(code, 4);
	bankMapper->addMapping(bankName, 3);
	bankMapper->toFirst();

	QDataWidgetMapper* contributionMapper = new QDataWidgetMapper(this);
	contributionMapper->setModel(memberDetailModel.getContributionTableModel());
	contributionMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	contributionMapper->addMapping(contributionInfo, 6);
	contributionMapper->addMapping(donation, 3);
	contributionMapper->addMapping(fee, 2);
	contributionMapper->toFirst();

	QDataWidgetMapper* ressourcenMapper = new QDataWidgetMapper(this);
	ressourcenMapper->setModel(memberDetailModel.getRessourcenTableModel());
	ressourcenMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	ressourcenMapper->addMapping(email, 2);
	ressourcenMapper->toFirst();
}

void MemberDialog::setMemberId(const int& anId)
{
	memberDetailModel.setMemberId(anId);
	QString id;
	id.setNum(anId);
	memberId->setText(id);
}

void MemberDialog::saveMember()
{
//	ClubFrontend::Member* const member = controller->getMember();
//	member->setName(memberName->text().toStdString());
//	member->setFirstname(firstName->text().toStdString());
//	member->setNickname(nickname->text().toStdString());
//	member->setStreet(street->text().toStdString());
//	member->setCity(city->text().toStdString());
//	member->setZipCode(zipcode->text().toInt());
//	member->setEmail(email->text().toStdString());
//	member->setEntryDate(entryDate->text().toStdString());
//	member->setInfo(info->toPlainText().toStdString());
//
//	ClubFrontend::Bank* const bank = controller->getBank();
//	bank->setAccount(account->text().toInt());
//	bank->setCode(code->text().toInt());
//	bank->setName(bankName->text().toStdString());
//
//	ClubFrontend::Contribution* contribution = controller->getContribution();
//	contribution->setDonation(donation->text().toInt());
//	contribution->setFee(fee->text().toInt());
//	contribution->setInfo(contributionInfo->text().toStdString());
//
//	controller->saveMember(member,bank,contribution);
}

}
