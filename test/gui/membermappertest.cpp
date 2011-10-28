#include "membermappertest.h"

#include "gui/membermapper.h"
#include "gui/mainwindow.h"

#include "model/databasestructure.h"

#include "testconfig.h"
#include "gui/membermapper.h"
#include "database/databaseutil.h"
#include "ui_mainwindow.h"
#include "member.h"
#include "memberfactory.h"

#include <QtCore>
#include <QtSql>
#include <QtGui>

namespace ClubFrontendTest
{
namespace Gui
{

void MemberMapperTest::initTestCase()
{
    qttestutil::database::DatabaseUtil database(DATABASEDRIVER);
    database.open(DATABASE);
    database.read(SQLTESTFILE);
}

void MemberMapperTest::showMember()
{
    Ui::MainWindow mainWindow;
    ClubFrontend::Gui::MemberMapper memberMapper(&mainWindow);
    QMainWindow window;
    mainWindow.setupUi(&window);
    memberMapper.initUi();

    memberMapper.showMember(ClubFrontend::MemberFactory::createMember(1025));

    QLabel *memberId = mainWindow.memberId;
    QCOMPARE(memberId->text(), QString("1025"));

    QLineEdit *firstName = mainWindow.firstName;
    QCOMPARE(firstName->text(), QString("James T"));

    QLineEdit *memberName = mainWindow.memberName;
    QCOMPARE(memberName->text(), QString("Kirk"));

    QLineEdit *nickname = mainWindow.nickname;
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));

    QPlainTextEdit *info = mainWindow.info;
    QCOMPARE(info->toPlainText(), QString(""));

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

    QLineEdit *account = mainWindow.account;
    QCOMPARE(account->text(), QString("12234569"));

    QLineEdit *code = mainWindow.code;
    QCOMPARE(code->text(), QString("9004010"));

    QLineEdit *bankName = mainWindow.bankName;
    QCOMPARE(bankName->text(), QString("sparstrumpf"));
}

void MemberMapperTest::changeMember()
{
    Ui::MainWindow mainWindow;
    ClubFrontend::Gui::MemberMapper memberMapper(&mainWindow);
    QMainWindow window;
    mainWindow.setupUi(&window);
    memberMapper.initUi();

    memberMapper.showMember(ClubFrontend::MemberFactory::createMember(1025));

    QLabel *id = mainWindow.memberId;
    QCOMPARE(id->text(), QString("1025"));

    QLineEdit *firstName = mainWindow.firstName;
    QCOMPARE(firstName->text(), QString("James T"));

    QLineEdit *memberName = mainWindow.memberName;
    QCOMPARE(memberName->text(), QString("Kirk"));

    QLineEdit *nickname = mainWindow.nickname;
    QCOMPARE(nickname->text(), QString("Capt. Kirk"));

    QPlainTextEdit *info = mainWindow.info;
    QCOMPARE(info->toPlainText(), QString(""));

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

    QLineEdit *account = mainWindow.account;
    QCOMPARE(account->text(), QString("12234569"));

    QLineEdit *code = mainWindow.code;
    QCOMPARE(code->text(), QString("9004010"));

    QLineEdit *bankName = mainWindow.bankName;
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

    QDialogButtonBox *buttonBox = mainWindow.buttonBox;
    QPushButton *saveButton = buttonBox->button(QDialogButtonBox::SaveAll);
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
    QCOMPARE(donation->text(), QString("100"));
    QCOMPARE(fee->text(), QString("99"));
    QCOMPARE(account->text(), QString("123456789"));
    QCOMPARE(bankName->text(), QString("Galaxy"));
    QCOMPARE(code->text(), QString("98765432"));
    QCOMPARE(info->toPlainText(), QString("Lalala"));

    const QString whereClause(" where dorfmitglied_pkey=1025");

    using ClubFrontend::Model::MemberTable;
    QSqlQuery query;
    query.exec("select * from " + MemberTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(MemberTable::FirstName).toString(), QString("Jonathan"));
    QCOMPARE(query.value(MemberTable::Name).toString(), QString("Archer"));
    QCOMPARE(query.value(MemberTable::NickName).toString(), QString("Captain"));
    QCOMPARE(query.value(MemberTable::Info).toString(), QString("Lalala"));

    using ClubFrontend::Model::AddressTable;
    query.exec("select * from " + AddressTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(AddressTable::Street).toString(), QString("NCC-1701"));
    QCOMPARE(query.value(AddressTable::ZipCode).toString(), QString("98765"));
    QCOMPARE(query.value(AddressTable::Town).toString(), QString("Dtown"));

    using ClubFrontend::Model::ContributionTable;
    query.exec("select * from " + ContributionTable::TABLENAME + whereClause +
               " order by " + ContributionTable::COLUMNNAME[ContributionTable::ValidFrom] + " desc");
    query.next();
    QCOMPARE(query.value(ContributionTable::Fee).toInt(), 99);
    QCOMPARE(query.value(ContributionTable::Donation).toInt(), 100);
    QCOMPARE(query.value(ContributionTable::Info).toString(), QString("Kohle"));

    using ClubFrontend::Model::BankAccountTable;
    query.exec("select * from " + BankAccountTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(BankAccountTable::Code).toInt(), 98765432);
    QCOMPARE(query.value(BankAccountTable::AccountNr).toInt(), 123456789);
    QCOMPARE(query.value(BankAccountTable::BankName).toString(), QString("Galaxy"));

    using ClubFrontend::Model::RessourcenTable;
    query.exec("select * from " + RessourcenTable::TABLENAME + whereClause);
    query.next();
    QCOMPARE(query.value(RessourcenTable::EmailAdress).toString(), QString("foo@bar.tx"));
}

}
}

QTEST_MAIN(ClubFrontendTest::Gui::MemberMapperTest)
#include "membermappertest.moc"
