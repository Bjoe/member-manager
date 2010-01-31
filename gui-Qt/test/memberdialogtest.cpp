#include <QtGui>
#include <gmock/gmock.h>

#include "../src/member.h"

#include "membermock.h"
#include "bankmock.h"
#include "contributionmock.h"
#include "controllermock.h"
#include "memberdialogtest.h"

using ::testing::Return;

namespace ClubFrontendTest
{

void MemberDialogTest::setMemberId()
{
	MemberMock member;
	BankMock bank;
	ContributionMock contribution;

	ControllerMock controller(&member, &bank, &contribution);
	GuiManagement::MemberDialog dialog(controller);

	dialog.setMemberId(23);

	QString id;
	id.setNum(23);
	QCOMPARE(dialog.memberId->text(), id);
}

void MemberDialogTest::newMember()
{
	MemberMock memberMock;
	EXPECT_CALL(memberMock, setName("Mc Kay")).Times(1);
	EXPECT_CALL(memberMock, setFirstname("Rodney")).Times(1);
	EXPECT_CALL(memberMock, setNickname("Rod")).Times(1);
	EXPECT_CALL(memberMock, setStreet("Atlantis")).Times(1);
	EXPECT_CALL(memberMock, setCity("Pegasus")).Times(1);
	EXPECT_CALL(memberMock, setZipCode(40215)).Times(1);
	EXPECT_CALL(memberMock, setEmail("rod@atlantis.pegasus")).Times(1);
	EXPECT_CALL(memberMock, setEntryDate("08.01.09")).Times(1);
	EXPECT_CALL(memberMock, setInfo("Foo")).Times(1);
		
	BankMock bankMock;
	EXPECT_CALL(bankMock, setAccount(123456789)).Times(1);
	EXPECT_CALL(bankMock, setName("Galaxy Bank")).Times(1);
	EXPECT_CALL(bankMock, setCode(98765432)).Times(1);
	
	ContributionMock contributionMock;
	EXPECT_CALL(contributionMock, setFee(15)).Times(1);
	EXPECT_CALL(contributionMock, setDonation(5)).Times(1);	
	EXPECT_CALL(contributionMock, setInfo("Info")).Times(1);
		
	ControllerMock controller(&memberMock, &bankMock, &contributionMock);
	GuiManagement::MemberDialog dialog(controller);

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
	MemberMock member;
	EXPECT_CALL(member, getCity())
		.Times(1)
		.WillOnce(Return("Dtown"));
	EXPECT_CALL(member, getEmail())
		.Times(1)
		.WillOnce(Return("foo@bar.tx"));
	EXPECT_CALL(member, getEntryDate())
		.Times(1)
		.WillOnce(Return("15.07.2006"));
	EXPECT_CALL(member, getFirstname())
		.Times(1)
		.WillOnce(Return("Jonathen"));
	EXPECT_CALL(member, getId())
		.Times(1)
		.WillOnce(Return(23));
	EXPECT_CALL(member, getInfo())
		.Times(1)
		.WillOnce(Return("Lalala"));
	EXPECT_CALL(member, getName())
		.Times(1)
		.WillOnce(Return("Archer"));
	EXPECT_CALL(member, getNickname())
		.Times(1)
		.WillOnce(Return("Captain"));
	EXPECT_CALL(member, getStreet())
		.Times(1)
		.WillOnce(Return("NCC-1701"));
	EXPECT_CALL(member, getZipCode())
		.Times(1)
		.WillOnce(Return(98765));

	BankMock bank;
	EXPECT_CALL(bank, getAccount())
		.Times(1)
		.WillOnce(Return(123456789));
	EXPECT_CALL(bank, getCode())
		.Times(1)
		.WillOnce(Return(98765));
	EXPECT_CALL(bank, getName())
		.Times(1)
		.WillOnce(Return("Galaxy"));
		
	ContributionMock contribution;
	EXPECT_CALL(contribution, getDonation())
		.Times(1)
		.WillOnce(Return(1));
	EXPECT_CALL(contribution, getFee())
		.Times(1)
		.WillOnce(Return(15));
	EXPECT_CALL(contribution, getInfo())
		.Times(1)
		.WillOnce(Return("Kohle"));
//	EXPECT_CALL(contribution, getValidFrom())
//		.Times(1)
//		.WillOnce(Return("13.09.2006"));
//	contribution->setValidFrom("13.09.2006");


	ControllerMock controller(&member, &bank, &contribution);
	GuiManagement::MemberDialog dialog(controller);
	dialog.showMember();
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
