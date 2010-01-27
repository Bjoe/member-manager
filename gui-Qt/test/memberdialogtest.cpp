#include <QtGui>

#include "../src/member.h"

#include "membermock.h"
#include "bankmock.h"
#include "contributionmock.h"
#include "resourcesmock.h"
#include "controllermock.h"
#include "memberdialogtest.h"

namespace ClubFrontendTest {

void MemberDialogTest::setMemberId()
{
    MemberMock* const member = new MemberMock;
    BankMock* const bank = new BankMock;
    ContributionMock* const contribution = new ContributionMock;
    ResourcesMock* const resources = new ResourcesMock;

    ControllerMock controller(member,bank,contribution,resources);
    GuiManagement::MemberDialog dialog(controller);

    dialog.setMemberId(23);

    QString id;
    id.setNum(23);
    QCOMPARE(dialog.memberId->text(), id);

    delete member;
    delete bank;
    delete contribution;
    delete resources;
}

void MemberDialogTest::newMember()
{
    MemberMock* const memberMock = new MemberMock;
	BankMock* const bankMock = new BankMock;
    ContributionMock* const contributionMock = new ContributionMock;
    ResourcesMock* const resourcesMock = new ResourcesMock;

    ControllerMock controller(memberMock,bankMock,contributionMock,resourcesMock);
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

    const MemberMock* member = controller.getMemberMock();
    QCOMPARE(QString::fromStdString(member->getName()), QString("Mc Kay"));
    QCOMPARE(QString::fromStdString(member->getFirstname()), QString("Rodney"));
    QCOMPARE(QString::fromStdString(member->getNickname()), QString("Rod"));
    QCOMPARE(QString::fromStdString(member->getStreet()), QString("Atlantis"));
    QCOMPARE(QString::fromStdString(member->getCity()), QString("Pegasus"));
    QCOMPARE(member->getZipCode(), 40215);
    QCOMPARE(QString::fromStdString(member->getEmail()), QString("rod@atlantis.pegasus"));
    QCOMPARE(QString::fromStdString(member->getEntryDate()), QString("08.01.09"));
    QCOMPARE(QString::fromStdString(member->getInfo()), QString("Foo"));
    delete member;

    const BankMock* bank = controller.getBankMock();
    QCOMPARE(QString::fromStdString(bank->getName()), QString("Galaxy Bank"));
    QCOMPARE(bank->getCode(),98765432);
    QCOMPARE(bank->getAccount(),123456789);
    delete bank;

    const ResourcesMock* resources = controller.getResourcesMock();
    QCOMPARE(QString::fromStdString(resources->getEmailIntern()),QString("rod@atlantis.pegasus"));
    delete resources;

    const ContributionMock* contribution = controller.getContributionMock();
    QCOMPARE(QString::fromStdString(contribution->getInfo()),QString("Info"));
    QCOMPARE(contribution->getDonation(),5);
    QCOMPARE(contribution->getFee(),15);
    delete contribution;
}

void MemberDialogTest::changeMember()
{
    MemberMock* const member = new MemberMock;
    member->setCity("Dtown");
    member->setEmail("foo@bar.tx");
    member->setEntryDate("15.07.2006");
    member->setFirstname("Jonathan");
    member->setId(23);
    member->setInfo("Lalala");
    member->setName("Archer");
    member->setNickname("Captain");
    member->setStreet("NCC-1701");
    member->setZipCode(98765);

    BankMock* const bank = new BankMock;
    bank->setAccount(123456789);
    bank->setCode(98765);
    bank->setName("Galaxy");

    ContributionMock* const contribution = new ContributionMock;
    contribution->setDonation(1);
    contribution->setFee(15);
    contribution->setInfo("Kohle");
    contribution->setValidFrom("13.09.2006");

    ResourcesMock* const resources = new ResourcesMock;
    resources->setEmailIntern("foo@bar.tx");

    ControllerMock controller(member, bank, contribution, resources);
    GuiManagement::MemberDialog dialog(controller);
	dialog.showMember();
		
    QCOMPARE(dialog.firstName->text(), QString("Jonathan"));
    QCOMPARE(dialog.memberName->text(), QString("Archer"));
    QCOMPARE(dialog.nickname->text(), QString("Captain"));
    QCOMPARE(dialog.memberId->text(), QString("23"));
    QCOMPARE(dialog.city->text(), QString("Dtown"));
    QCOMPARE(dialog.street->text(), QString("NCC-1701"));
    QCOMPARE(dialog.zipcode->text(), QString("98765"));
    QCOMPARE(dialog.email->text(), QString("foo@bar.tx"));
    QCOMPARE(dialog.entryDate->text(), QString("15.07.06"));
    QCOMPARE(dialog.contributionInfo->text(), QString("Kohle"));
    QCOMPARE(dialog.donation->text(), QString("1"));
    QCOMPARE(dialog.fee->text(), QString("15"));
    QCOMPARE(dialog.account->text(), QString("123456789"));
    QCOMPARE(dialog.bankName->text(), QString("Galaxy"));
    QCOMPARE(dialog.code->text(), QString("98765"));
    //QCOMPARE(dialog.info->toPlainText(), QString("Lalala"));

    delete member;
    delete bank;
    delete contribution;
    delete resources;
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
