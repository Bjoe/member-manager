#include <QtGui>

#include "MemberDialog.h"

namespace ClubFrontend
{

MemberDialog::MemberDialog(QWidget *parent) :
		QWidget(parent)
{
	setupUi(this);
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveMember()));
}

void MemberDialog::showMember(const QSqlRecord &aRecord) const
{
	// TODO QDataWidgetMapper
	int id = aRecord.value("dorfmitglied_pkey").toInt();
	memberId->setText(QString::number(id));
	firstName->setText(aRecord.value("vorname").toString());
	memberName->setText(aRecord.value("name").toString());
	nickname->setText(aRecord.value("nickname").toString());
	city->setText(aRecord.value("ort").toString());
	street->setText(aRecord.value("strasse").toString());
	zipcode->setText(aRecord.value("plz").toString());
	email->setText(aRecord.value("email").toString());
	entryDate->setDate(aRecord.value("eintrittsdatum").toDate());
	info->setPlainText(aRecord.value("info").toString());
	contributionInfo->setText(aRecord.value("btinfo").toString());
	double donationValue = aRecord.value("spende").toDouble();
	donation->setText(QString::number(donationValue));
	double feeValue = aRecord.value("beitrag").toDouble();
	fee->setText(QString::number(feeValue));
	int accountValue = aRecord.value("kontonr").toInt();
	account->setText(QString::number(accountValue));
	int codeValue = aRecord.value("blz").toInt();
	code->setText(QString::number(codeValue));
	bankName->setText(aRecord.value("bank").toString());
}

void MemberDialog::setMemberId(const int& anId)
{
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
