#include <QtGui>
#include <QtSql>

#include "DatabaseStructure.h"
#include "TestData.h"

#include "MemberDialogTest.h"

namespace ClubFrontendTest
{

void MemberDialogTest::initTestCase() {
	TestData testData;
	testData.createFakeMemberTable();
	testData.createFakeAdressTable();
	testData.createFakeBankTable();
	testData.createFakeRessourcenTable();
	testData.createFakeContributionTable();
}

void MemberDialogTest::showMember() {
	ClubFrontend::MemberDialog dialog(1025);

	QCOMPARE(dialog.memberId->text(), QString("1025"));
	QCOMPARE(dialog.firstName->text(), QString("James T"));
	QCOMPARE(dialog.memberName->text(), QString("Kirk"));
	QCOMPARE(dialog.nickname->text(), QString("Capt. Kirk"));
	QCOMPARE(dialog.info->toPlainText(), QString(""));
	QCOMPARE(dialog.city->text(), QString("Bloedeldorf"));
	QCOMPARE(dialog.street->text(), QString("Industriestr. 23"));
	QCOMPARE(dialog.zipcode->text(), QString("90546"));
	QCOMPARE(dialog.email->text(), QString("fooo@baaar.xx"));
	QCOMPARE(dialog.entryDate->text(), QString("24.04.01"));
	QCOMPARE(dialog.contributionInfo->text(), QString("Spende wird eingestellt"));
	QCOMPARE(dialog.donation->text(), QString("0"));
	QCOMPARE(dialog.fee->text(), QString("15"));
	QCOMPARE(dialog.account->text(), QString("12234569"));
	QCOMPARE(dialog.code->text(), QString("9004010"));
	QCOMPARE(dialog.bankName->text(), QString("sparstrumpf"));
}

void MemberDialogTest::newMember()
{
	ClubFrontend::MemberDialog dialog(0);

	QTest::keyClicks(dialog.memberName, "Mc Kay");
	QTest::keyClicks(dialog.firstName, "Rodney");
	QTest::keyClicks(dialog.nickname, "Rod");

	QTest::keyClicks(dialog.street, "Atlantis");
	QTest::keyClicks(dialog.city, "Pegasus");
	QTest::keyClicks(dialog.zipcode, "40215");

	QTest::keyClicks(dialog.email, "rod@atlantis.pegasus");
	QTest::keyClicks(dialog.entryDate, "01.01.09");

	QTest::keyClicks(dialog.fee, "15");
	QTest::keyClicks(dialog.donation, "5");
	QTest::keyClicks(dialog.contributionInfo, "Info");

	QTest::keyClicks(dialog.account, "123456789");
	QTest::keyClicks(dialog.bankName, "Galaxy Bank");
	QTest::keyClicks(dialog.code, "98765432");

	QTest::keyClicks(dialog.info, "Foo");

	QTest::mouseClick(dialog.buttonBox->button(QDialogButtonBox::Save),Qt::LeftButton);


}

void MemberDialogTest::changeMember()
{
	ClubFrontend::MemberDialog dialog(1025);

	QLabel* id = dialog.findChild<QLabel *>("memberId");
	QCOMPARE(id->text(), QString("1025"));

	QCOMPARE(dialog.memberId->text(), QString("1025"));
	QCOMPARE(dialog.firstName->text(), QString("James T"));
	QCOMPARE(dialog.memberName->text(), QString("Kirk"));
	QCOMPARE(dialog.nickname->text(), QString("Capt. Kirk"));
	QCOMPARE(dialog.info->toPlainText(), QString(""));
	QCOMPARE(dialog.city->text(), QString("Bloedeldorf"));
	QCOMPARE(dialog.street->text(), QString("Industriestr. 23"));
	QCOMPARE(dialog.zipcode->text(), QString("90546"));
	QCOMPARE(dialog.email->text(), QString("fooo@baaar.xx"));
	QCOMPARE(dialog.entryDate->text(), QString("24.04.01"));
	QCOMPARE(dialog.contributionInfo->text(), QString("Spende wird eingestellt"));
	QCOMPARE(dialog.donation->text(), QString("0"));
	QCOMPARE(dialog.fee->text(), QString("15"));
	QCOMPARE(dialog.account->text(), QString("12234569"));
	QCOMPARE(dialog.code->text(), QString("9004010"));
	QCOMPARE(dialog.bankName->text(), QString("sparstrumpf"));

	dialog.memberName->clear();
	QTest::keyClicks(dialog.memberName, "Archer");
	dialog.firstName->clear();
	QTest::keyClicks(dialog.firstName, "Jonathan");
	dialog.nickname->clear();
	QTest::keyClicks(dialog.nickname, "Captain");

	dialog.street->clear();
	QTest::keyClicks(dialog.street, "NCC-1701");
	dialog.city->clear();
	QTest::keyClicks(dialog.city, "Dtown");
	dialog.zipcode->clear();
	QTest::keyClicks(dialog.zipcode, "98765");

	dialog.email->clear();
	QTest::keyClicks(dialog.email, "foo@bar.tx");
	QTest::keyClicks(dialog.entryDate, "15.07.06");

	dialog.fee->clear();
	QTest::keyClicks(dialog.fee, "16");
	dialog.donation->clear();
	QTest::keyClicks(dialog.donation, "1");
	dialog.contributionInfo->clear();
	QTest::keyClicks(dialog.contributionInfo, "Kohle");

	dialog.account->clear();
	QTest::keyClicks(dialog.account, "123456789");
	dialog.bankName->clear();
	QTest::keyClicks(dialog.bankName, "Galaxy");
	dialog.code->clear();
	QTest::keyClicks(dialog.code, "98765432");

	dialog.info->clear();
	QTest::keyClicks(dialog.info, "Lalala");

	QTest::mouseClick(dialog.buttonBox->button(QDialogButtonBox::Save),Qt::LeftButton);

	QCOMPARE(dialog.firstName->text(), QString("Jonathan"));
	QCOMPARE(dialog.memberName->text(), QString("Archer"));
	QCOMPARE(dialog.nickname->text(), QString("Captain"));
	QCOMPARE(dialog.memberId->text(), QString("1025"));
	QCOMPARE(dialog.city->text(), QString("Dtown"));
	QCOMPARE(dialog.street->text(), QString("NCC-1701"));
	QCOMPARE(dialog.zipcode->text(), QString("98765"));
	QCOMPARE(dialog.email->text(), QString("foo@bar.tx"));
	//QCOMPARE(dialog.entryDate->text(), QString("15.07.06"));
	QCOMPARE(dialog.contributionInfo->text(), QString("Kohle"));
	QCOMPARE(dialog.donation->text(), QString("1"));
	QCOMPARE(dialog.fee->text(), QString("16"));
	QCOMPARE(dialog.account->text(), QString("123456789"));
	QCOMPARE(dialog.bankName->text(), QString("Galaxy"));
	QCOMPARE(dialog.code->text(), QString("98765432"));
	QCOMPARE(dialog.info->toPlainText(), QString("Lalala"));

	const QString whereClause(" where dorfmitglied_pkey=1025");

	using ClubFrontend::MemberTable;
	QSqlQuery query;
	query.exec("select * from " + MemberTable::TABLENAME + whereClause);
	query.next();
	QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
	QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
	// TODO weiter Testen

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

void MemberDialogTest::foo()
{
	QString foo("10");
	QCOMPARE(QString("10"),foo);
	int ifoo = foo.toInt();
	QCOMPARE(10,ifoo);

	int i = 1;
	int& r = i;
	int x = r;

	QCOMPARE(i,1);
	QCOMPARE(r,1);
	QCOMPARE(x,1);

	r = 2;

	QCOMPARE(i,2);
	QCOMPARE(r,2);
	QCOMPARE(x,1);

	i = 4;

	QCOMPARE(i,4);
	QCOMPARE(r,4);
	QCOMPARE(x,1);

	x = 3;

	QCOMPARE(i,4);
	QCOMPARE(r,4);
	QCOMPARE(x,3);

}

}
