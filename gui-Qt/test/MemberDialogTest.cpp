#include "MemberDialogTest.h"

#include "MemberDialog.h"

#include "DatabaseStructure.h"
#include "TestData.h"

#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSqlQuery>
#include <QString>
#include <QPushButton>
#include <QDialogButtonBox>

namespace ClubFrontendTest
{

void MemberDialogTest::initTestCase()
{
	TestData testData;
	testData.createFakeMemberTable();
	testData.createFakeAdressTable();
	testData.createFakeBankTable();
	testData.createFakeRessourcenTable();
	testData.createFakeContributionTable();
}

void MemberDialogTest::showMember()
{
	ClubFrontend::MemberDialog dialog(1025);

	QLabel* memberId = dialog.findChild<QLabel*> ("memberId");
	QCOMPARE(memberId->text(), QString("1025"));

	QLineEdit* firstName = dialog.findChild<QLineEdit*> ("firstName");
	QCOMPARE(firstName->text(), QString("James T"));

	QLineEdit* memberName = dialog.findChild<QLineEdit*> ("memberName");
	QCOMPARE(memberName->text(), QString("Kirk"));

	QLineEdit* nickname = dialog.findChild<QLineEdit*> ("nickname");
	QCOMPARE(nickname->text(), QString("Capt. Kirk"));

	QPlainTextEdit* info = dialog.findChild<QPlainTextEdit*> ("info");
	QCOMPARE(info->toPlainText(), QString(""));

	QLineEdit* city = dialog.findChild<QLineEdit*> ("city");
	QCOMPARE(city->text(), QString("Bloedeldorf"));

	QLineEdit* street = dialog.findChild<QLineEdit*> ("street");
	QCOMPARE(street->text(), QString("Industriestr. 23"));

	QLineEdit* zipcode = dialog.findChild<QLineEdit*> ("zipcode");
	QCOMPARE(zipcode->text(), QString("90546"));

	QLineEdit* email = dialog.findChild<QLineEdit*> ("email");
	QCOMPARE(email->text(), QString("fooo@baaar.xx"));

	QDateEdit* entryDate = dialog.findChild<QDateEdit*> ("entryDate");
	QCOMPARE(entryDate->text(), QString("24.04.01"));

	QLineEdit* contributionInfo = dialog.findChild<QLineEdit*> (
			"contributionInfo");
	QCOMPARE(contributionInfo->text(), QString("Spende wird eingestellt"));

	QLineEdit* donation = dialog.findChild<QLineEdit*> ("donation");
	QCOMPARE(donation->text(), QString("0"));

	QLineEdit* fee = dialog.findChild<QLineEdit*> ("fee");
	QCOMPARE(fee->text(), QString("15"));

	QLineEdit* account = dialog.findChild<QLineEdit*> ("account");
	QCOMPARE(account->text(), QString("12234569"));

	QLineEdit* code = dialog.findChild<QLineEdit*> ("code");
	QCOMPARE(code->text(), QString("9004010"));

	QLineEdit* bankName = dialog.findChild<QLineEdit*> ("bankName");
	QCOMPARE(bankName->text(), QString("sparstrumpf"));
}

void MemberDialogTest::newMember()
{
	ClubFrontend::MemberDialog dialog(0);

	QLineEdit* memberName = dialog.findChild<QLineEdit*> ("memberName");
	QTest::keyClicks(memberName, "Mc Kay");

	QLineEdit* firstName = dialog.findChild<QLineEdit*> ("firstName");
	QTest::keyClicks(firstName, "Rodney");

	QLineEdit* nickname = dialog.findChild<QLineEdit*> ("nickname");
	QTest::keyClicks(nickname, "Rod");

	QLineEdit* street = dialog.findChild<QLineEdit*> ("street");
	QTest::keyClicks(street, "Atlantis");

	QLineEdit* city = dialog.findChild<QLineEdit*> ("city");
	QTest::keyClicks(city, "Pegasus");

	QLineEdit* zipcode = dialog.findChild<QLineEdit*> ("zipcode");
	QTest::keyClicks(zipcode, "40215");

	QLineEdit* email = dialog.findChild<QLineEdit*> ("email");
	QTest::keyClicks(email, "rod@atlantis.pegasus");

	QDateEdit* entryDate = dialog.findChild<QDateEdit*> ("entryDate");
	QTest::keyClicks(entryDate, "01.01.09");

	QLineEdit* fee = dialog.findChild<QLineEdit*> ("fee");
	QTest::keyClicks(fee, "15");

	QLineEdit* donation = dialog.findChild<QLineEdit*> ("donation");
	QTest::keyClicks(donation, "5");

	QLineEdit* contributionInfo = dialog.findChild<QLineEdit*> (
			"contributionInfo");
	QTest::keyClicks(contributionInfo, "Info");

	QLineEdit* account = dialog.findChild<QLineEdit*> ("account");
	QTest::keyClicks(account, "123456789");

	QLineEdit* bankName = dialog.findChild<QLineEdit*> ("bankName");
	QTest::keyClicks(bankName, "Galaxy Bank");

	QLineEdit* code = dialog.findChild<QLineEdit*> ("code");
	QTest::keyClicks(code, "98765432");

	QPlainTextEdit* info = dialog.findChild<QPlainTextEdit*> ("info");
	QTest::keyClicks(info, "Foo");

	QDialogButtonBox* buttonBox = dialog.findChild<QDialogButtonBox*> (
			"buttonBox");
	QPushButton* saveButton = buttonBox->button(QDialogButtonBox::Save);
	QTest::mouseClick(saveButton, Qt::LeftButton);
}

void MemberDialogTest::changeMember()
{
	ClubFrontend::MemberDialog dialog(1025);

	QLabel* id = dialog.findChild<QLabel *> ("memberId");
	QCOMPARE(id->text(), QString("1025"));

	QLineEdit* firstName = dialog.findChild<QLineEdit*> ("firstName");
	QCOMPARE(firstName->text(), QString("James T"));

	QLineEdit* memberName = dialog.findChild<QLineEdit*> ("memberName");
	QCOMPARE(memberName->text(), QString("Kirk"));

	QLineEdit* nickname = dialog.findChild<QLineEdit*> ("nickname");
	QCOMPARE(nickname->text(), QString("Capt. Kirk"));

	QPlainTextEdit* info = dialog.findChild<QPlainTextEdit*> ("info");
	QCOMPARE(info->toPlainText(), QString(""));

	QLineEdit* city = dialog.findChild<QLineEdit*> ("city");
	QCOMPARE(city->text(), QString("Bloedeldorf"));

	QLineEdit* street = dialog.findChild<QLineEdit*> ("street");
	QCOMPARE(street->text(), QString("Industriestr. 23"));

	QLineEdit* zipcode = dialog.findChild<QLineEdit*> ("zipcode");
	QCOMPARE(zipcode->text(), QString("90546"));

	QLineEdit* email = dialog.findChild<QLineEdit*> ("email");
	QCOMPARE(email->text(), QString("fooo@baaar.xx"));

	QDateEdit* entryDate = dialog.findChild<QDateEdit*> ("entryDate");
	QCOMPARE(entryDate->text(), QString("24.04.01"));

	QLineEdit* contributionInfo = dialog.findChild<QLineEdit*> (
			"contributionInfo");
	QCOMPARE(contributionInfo->text(), QString("Spende wird eingestellt"));

	QLineEdit* donation = dialog.findChild<QLineEdit*> ("donation");
	QCOMPARE(donation->text(), QString("0"));

	QLineEdit* fee = dialog.findChild<QLineEdit*> ("fee");
	QCOMPARE(fee->text(), QString("15"));

	QLineEdit* account = dialog.findChild<QLineEdit*> ("account");
	QCOMPARE(account->text(), QString("12234569"));

	QLineEdit* code = dialog.findChild<QLineEdit*> ("code");
	QCOMPARE(code->text(), QString("9004010"));

	QLineEdit* bankName = dialog.findChild<QLineEdit*> ("bankName");
	QCOMPARE(bankName->text(), QString("sparstrumpf"));

	memberName->clear();
	QTest::keyClicks(memberName, "Archer");
	firstName->clear();
	QTest::keyClicks(firstName, "Jonathan");
	nickname->clear();
	QTest::keyClicks(nickname, "Captain");

	street->clear();
	QTest::keyClicks(street, "NCC-1701");
	city->clear();
	QTest::keyClicks(city, "Dtown");
	zipcode->clear();
	QTest::keyClicks(zipcode, "98765");

	email->clear();
	QTest::keyClicks(email, "foo@bar.tx");
	QTest::keyClicks(entryDate, "15.07.06");

	fee->clear();
	QTest::keyClicks(fee, "16");
	donation->clear();
	QTest::keyClicks(donation, "1");
	contributionInfo->clear();
	QTest::keyClicks(contributionInfo, "Kohle");

	account->clear();
	QTest::keyClicks(account, "123456789");
	bankName->clear();
	QTest::keyClicks(bankName, "Galaxy");
	code->clear();
	QTest::keyClicks(code, "98765432");

	info->clear();
	QTest::keyClicks(info, "Lalala");

	QDialogButtonBox* buttonBox = dialog.findChild<QDialogButtonBox*> (
			"buttonBox");
	QPushButton* saveButton = buttonBox->button(QDialogButtonBox::Save);
	QTest::mouseClick(saveButton, Qt::LeftButton);

	QCOMPARE(firstName->text(), QString("Jonathan"));
	QCOMPARE(memberName->text(), QString("Archer"));
	QCOMPARE(nickname->text(), QString("Captain"));
	QCOMPARE(id->text(), QString("1025"));
	QCOMPARE(city->text(), QString("Dtown"));
	QCOMPARE(street->text(), QString("NCC-1701"));
	QCOMPARE(zipcode->text(), QString("98765"));
	QCOMPARE(email->text(), QString("foo@bar.tx"));
	//QCOMPARE(entryDate->text(), QString("15.07.06"));
	QCOMPARE(contributionInfo->text(), QString("Kohle"));
	QCOMPARE(donation->text(), QString("1"));
	QCOMPARE(fee->text(), QString("16"));
	QCOMPARE(account->text(), QString("123456789"));
	QCOMPARE(bankName->text(), QString("Galaxy"));
	QCOMPARE(code->text(), QString("98765432"));
	QCOMPARE(info->toPlainText(), QString("Lalala"));

	const QString whereClause(" where dorfmitglied_pkey=1025");

	using ClubFrontend::MemberTable;
	QSqlQuery query;
	query.exec("select * from " + MemberTable::TABLENAME + whereClause);
	query.next();
	QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
	QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
	QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
	QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));

	using ClubFrontend::AddressTable;
	query.exec("select * from " + AddressTable::TABLENAME + whereClause);
	query.next();
	QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
	QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
	QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

	using ClubFrontend::ContributionTable;
	query.exec("select * from " + ContributionTable::TABLENAME + whereClause);
	query.next();
	QCOMPARE(query.value(ContributionTable::Fee).toInt(), 16);
	QCOMPARE(query.value(ContributionTable::Donation).toInt(), 1);
	QCOMPARE(query.value(ContributionTable::Info).toString(), QString("Kohle"));

	using ClubFrontend::BankAccountTable;
	query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
	query.next();
	QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
	QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
	QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

	using ClubFrontend::RessourcenTable;
	query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
	query.next();
	QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

}
