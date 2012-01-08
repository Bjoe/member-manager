#include "memberdetailviewtest.h"

#include "gui/memberdetailview.h"

#include "ui_mainwindow.h"
#include "member.h"
#include "memberfactory.h"
#include "model/databasestructure.h"
#include "model/saldomodel.h"
#include "model/contributionmodel.h"
#include "testconfig.h"

#include <QtCore>
#include <QtSql>
#include <QtGui>

namespace membermanagertest
{
namespace gui
{

MemberDetailViewTest::MemberDetailViewTest() :
    database(DATABASEDRIVER)
{}

void MemberDetailViewTest::initTestCase()
{
    database.open(DATABASE);
}

void MemberDetailViewTest::initTest()
{
    database.read(SQLTESTFILE);
}

void MemberDetailViewTest::testShowMember()
{
    QMainWindow *qmainWindow = new QMainWindow();
    Ui::MainWindow mainWindow;
    mainWindow.setupUi(qmainWindow);
    membermanager::gui::MemberDetailView memberDetailView(&mainWindow);

    memberDetailView.showMember(membermanager::MemberFactory::createMember(1025));

    QLabel *memberId = mainWindow.memberId;
    QCOMPARE(memberId->text(), QString("1025"));

    QLineEdit *firstName = mainWindow.firstName;
    QCOMPARE(firstName->text(), QString("James T"));

    QLineEdit *memberName = mainWindow.memberName;
    QCOMPARE(memberName->text(), QString("Kirk"));

    QLineEdit *nickname = mainWindow.nickname;
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));

    QPlainTextEdit *info = mainWindow.info;
    QCOMPARE(info->toPlainText(), QString("Captain of the ncc-1701"));

    QLineEdit *city = mainWindow.city;
    QCOMPARE(city->text(), QString("Bloedeldorf"));

    QLineEdit *street = mainWindow.street;
    QCOMPARE(street->text(), QString("Industriestr. 23"));

    QLineEdit *zipcode = mainWindow.zipcode;
    QCOMPARE(zipcode->text(), QString("90546"));

    QLineEdit *email = mainWindow.email;
    QCOMPARE(email->text(), QString("fooo@baaar.xx"));

    QDateEdit *entryDate = mainWindow.entryDate;
    QCOMPARE(entryDate->text(), QString("24.04.01"));

    QLineEdit *contributionInfo = mainWindow.contributionInfo;
    QCOMPARE(contributionInfo->text(), QString("Beitragsaenderung"));

    QLineEdit *donation = mainWindow.donation;
    QCOMPARE(donation->text(), QString("1"));

    QLineEdit *fee = mainWindow.fee;
    QCOMPARE(fee->text(), QString("15"));

    QDateEdit *validFrom = mainWindow.validFrom;
    QCOMPARE(validFrom->text(), QString("01.05.07"));

    QLineEdit *account = mainWindow.account;
    QCOMPARE(account->text(), QString("12234569"));

    QLineEdit *code = mainWindow.code;
    QCOMPARE(code->text(), QString("9004010"));

    QLineEdit *bankName = mainWindow.bankName;
    QCOMPARE(bankName->text(), QString("sparstrumpf"));

    QCheckBox *deleted = mainWindow.deleted;
    QVERIFY(deleted->isChecked() == false);
}

void MemberDetailViewTest::testChangeMember()
{
    QMainWindow *qmainWindow = new QMainWindow();
    Ui::MainWindow mainWindow;
    mainWindow.setupUi(qmainWindow);
    membermanager::gui::MemberDetailView memberDetailView(&mainWindow);

    memberDetailView.showMember(membermanager::MemberFactory::createMember(1025));

    QLabel *id = mainWindow.memberId;
    QCOMPARE(id->text(), QString("1025"));

    QLineEdit *firstName = mainWindow.firstName;
    QCOMPARE(firstName->text(), QString("James T"));

    QLineEdit *memberName = mainWindow.memberName;
    QCOMPARE(memberName->text(), QString("Kirk"));

    QLineEdit *nickname = mainWindow.nickname;
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));

    QPlainTextEdit *info = mainWindow.info;
    QCOMPARE(info->toPlainText(), QString("Captain of the ncc-1701"));

    QLineEdit *city = mainWindow.city;
    QCOMPARE(city->text(), QString("Bloedeldorf"));

    QLineEdit *street = mainWindow.street;
    QCOMPARE(street->text(), QString("Industriestr. 23"));

    QLineEdit *zipcode = mainWindow.zipcode;
    QCOMPARE(zipcode->text(), QString("90546"));

    QLineEdit *email = mainWindow.email;
    QCOMPARE(email->text(), QString("fooo@baaar.xx"));

    QDateEdit *entryDate = mainWindow.entryDate;
    QCOMPARE(entryDate->text(), QString("24.04.01"));

    QLineEdit *contributionInfo = mainWindow.contributionInfo;
    QCOMPARE(contributionInfo->text(), QString("Beitragsaenderung"));

    QLineEdit *donation = mainWindow.donation;
    QCOMPARE(donation->text(), QString("1"));

    QLineEdit *fee = mainWindow.fee;
    QCOMPARE(fee->text(), QString("15"));

    QDateEdit *validFrom = mainWindow.validFrom;
    QCOMPARE(validFrom->text(), QString("01.05.07"));

    QLineEdit *account = mainWindow.account;
    QCOMPARE(account->text(), QString("12234569"));

    QLineEdit *code = mainWindow.code;
    QCOMPARE(code->text(), QString("9004010"));

    QLineEdit *bankName = mainWindow.bankName;
    QCOMPARE(bankName->text(), QString("sparstrumpf"));

    QCheckBox *deleted = mainWindow.deleted;
    QVERIFY(deleted->isChecked() == false);

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
    QTest::keyClicks(fee, "99");
    donation->clear();
    QTest::keyClicks(donation, "100");
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

    deleted->setChecked(true);

    memberDetailView.saveMember();

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
    QCOMPARE(donation->text(), QString("100"));
    QCOMPARE(fee->text(), QString("99"));
    QCOMPARE(account->text(), QString("123456789"));
    QCOMPARE(bankName->text(), QString("Galaxy"));
    QCOMPARE(code->text(), QString("98765432"));
    QCOMPARE(info->toPlainText(), QString("Lalala"));
    QVERIFY(deleted->isChecked());

    using membermanager::model::MemberTable;
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(1025);

    using membermanager::model::MemberTable;
    QSqlQuery query;
    query.exec("select * from " + MemberTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
    QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
    QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));
    QVERIFY(query.value(MemberTable::Deleted).toBool());

    using membermanager::model::AddressTable;
    query.exec("select * from " + AddressTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
    QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
    QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

    using membermanager::model::ContributionTable;
    query.exec("select * from " + ContributionTable::TABLENAME + whereClause +
               " order by " + ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " desc");
    query.next();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 99);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 100);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("Kohle"));

    using membermanager::model::BankAccountTable;
    query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
    QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
    QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

    using membermanager::model::RessourcenTable;
    query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

void MemberDetailViewTest::testChangeMemberWithNewContribution()
{
    QMainWindow *qmainWindow = new QMainWindow();
    Ui::MainWindow mainWindow;
    mainWindow.setupUi(qmainWindow);
    membermanager::gui::MemberDetailView memberDetailView(&mainWindow);

    memberDetailView.showMember(membermanager::MemberFactory::createMember(1025));

    QLabel *id = mainWindow.memberId;
    QCOMPARE(id->text(), QString("1025"));

    QLineEdit *firstName = mainWindow.firstName;
    QCOMPARE(firstName->text(), QString("James T"));

    QLineEdit *memberName = mainWindow.memberName;
    QCOMPARE(memberName->text(), QString("Kirk"));

    QLineEdit *nickname = mainWindow.nickname;
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));

    QPlainTextEdit *info = mainWindow.info;
    QCOMPARE(info->toPlainText(), QString("Captain of the ncc-1701"));

    QLineEdit *city = mainWindow.city;
    QCOMPARE(city->text(), QString("Bloedeldorf"));

    QLineEdit *street = mainWindow.street;
    QCOMPARE(street->text(), QString("Industriestr. 23"));

    QLineEdit *zipcode = mainWindow.zipcode;
    QCOMPARE(zipcode->text(), QString("90546"));

    QLineEdit *email = mainWindow.email;
    QCOMPARE(email->text(), QString("fooo@baaar.xx"));

    QDateEdit *entryDate = mainWindow.entryDate;
    QCOMPARE(entryDate->text(), QString("24.04.01"));

    QLineEdit *contributionInfo = mainWindow.contributionInfo;
    QCOMPARE(contributionInfo->text(), QString("Beitragsaenderung"));

    QLineEdit *donation = mainWindow.donation;
    QCOMPARE(donation->text(), QString("1"));

    QLineEdit *fee = mainWindow.fee;
    QCOMPARE(fee->text(), QString("15"));

    QDateEdit *validFrom = mainWindow.validFrom;
    QCOMPARE(validFrom->text(), QString("01.05.07"));

    QLineEdit *account = mainWindow.account;
    QCOMPARE(account->text(), QString("12234569"));

    QLineEdit *code = mainWindow.code;
    QCOMPARE(code->text(), QString("9004010"));

    QLineEdit *bankName = mainWindow.bankName;
    QCOMPARE(bankName->text(), QString("sparstrumpf"));


    memberDetailView.newFee();

    QCOMPARE(validFrom->date(), QDate::currentDate());
    QCOMPARE(donation->text(), QString("0"));
    QCOMPARE(fee->text(), QString("15"));
    QCOMPARE(contributionInfo->text(), QString("Beitragsänderung"));

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

    account->clear();
    QTest::keyClicks(account, "123456789");
    bankName->clear();
    QTest::keyClicks(bankName, "Galaxy");
    code->clear();
    QTest::keyClicks(code, "98765432");

    info->clear();
    QTest::keyClicks(info, "Lalala");

    memberDetailView.saveMember();

    QCOMPARE(firstName->text(), QString("Jonathan"));
    QCOMPARE(memberName->text(), QString("Archer"));
    QCOMPARE(nickname->text(), QString("Captain"));
    QCOMPARE(id->text(), QString("1025"));
    QCOMPARE(city->text(), QString("Dtown"));
    QCOMPARE(street->text(), QString("NCC-1701"));
    QCOMPARE(zipcode->text(), QString("98765"));
    QCOMPARE(email->text(), QString("foo@bar.tx"));
    //QCOMPARE(entryDate->text(), QString("15.07.06"));
    QCOMPARE(contributionInfo->text(), QString("Beitragsänderung"));
    QCOMPARE(donation->text(), QString("0"));
    QCOMPARE(fee->text(), QString("15"));
    QCOMPARE(account->text(), QString("123456789"));
    QCOMPARE(bankName->text(), QString("Galaxy"));
    QCOMPARE(code->text(), QString("98765432"));
    QCOMPARE(info->toPlainText(), QString("Lalala"));

    using membermanager::model::MemberTable;
    const QString whereClause = QString(" where %1=%2").arg(
                                    MemberTable::COLUMNNAME[MemberTable::MemberId])
                                .arg(1025);

    using membermanager::model::MemberTable;
    QSqlQuery query;
    query.exec("select * from " + MemberTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
    QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
    QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));

    using membermanager::model::AddressTable;
    query.exec("select * from " + AddressTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
    QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
    QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

    using membermanager::model::ContributionTable;
    query.exec("select * from " + ContributionTable::TABLENAME + whereClause +
               " order by " + ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " desc");
    query.next();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 15);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 0);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("Beitragsänderung"));

    using membermanager::model::BankAccountTable;
    query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
    QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
    QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

    using membermanager::model::RessourcenTable;
    query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

void MemberDetailViewTest::testgetSaldo()
{
    QMainWindow *qmainWindow = new QMainWindow();
    Ui::MainWindow mainWindow;
    mainWindow.setupUi(qmainWindow);
    membermanager::gui::MemberDetailView memberDetailView(&mainWindow);

    memberDetailView.showMember(membermanager::MemberFactory::createMember(1025));

    membermanager::model::SaldoModel model = memberDetailView.getSaldoModel();

    QCOMPARE(model.getMemberId(), QString("1025"));
}

void MemberDetailViewTest::testgetContribution()
{
    QMainWindow *qmainWindow = new QMainWindow();
    Ui::MainWindow mainWindow;
    mainWindow.setupUi(qmainWindow);
    membermanager::gui::MemberDetailView memberDetailView(&mainWindow);

    memberDetailView.showMember(membermanager::MemberFactory::createMember(1025));

    membermanager::model::ContributionModel model = memberDetailView.getContributionModel();

    QCOMPARE(model.getMemberId(), QString("1025"));
}

}
}

QTEST_MAIN(membermanagertest::gui::MemberDetailViewTest)
#include "memberdetailviewtest.moc"
