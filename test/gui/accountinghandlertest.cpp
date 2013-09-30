
#include <QtTest/QtTest>
#include <QSignalSpy>

#include <QSqlDatabase>
#include <QSqlError>

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QVariantMap>
#include <QFile>
#include <QTextStream>
#include <QRegExp>

#include <QSettings>

#include "QDjango.h"
#include "QDjangoQuerySet.h"

#include "testconfig.h"

#include "entity/member.h"
#include "entity/bankaccount.h"
#include "entity/contribution.h"
#include "entity/balance.h"

#include "accounting/memberaccountingdata.h"

#include "gui/accountinghandler.h"

namespace test {
namespace gui {

class AccountingHandlerTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetAccountingData();
    void testBook();
};

void AccountingHandlerTest::initTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase(DATABASEDRIVER);
    db.setDatabaseName(DATABASE);
    if (!db.open()) {
        QSqlError err = db.lastError();
        if (err.type() != QSqlError::NoError) {
            qWarning() << err.text();
        }
    }
    QDjango::setDatabase(db);

    QDjango::registerModel<membermanager::entity::Member>();
    QDjango::registerModel<membermanager::entity::Contribution>();
    QDjango::registerModel<membermanager::entity::BankAccount>();
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

    membermanager::entity::Member* member = new membermanager::entity::Member();
    member->setMemberId(1);
    member->setName("Kirk");
    member->setFirstname("James T.");
    member->setCollectionState(membermanager::entity::Member::CollectionState::known);
    member->save();

    membermanager::entity::BankAccount *bankAccount = new membermanager::entity::BankAccount();
    bankAccount->setMemberId(1);
    bankAccount->setAccountNumber("22334455");
    bankAccount->setCode("80070099");
    bankAccount->setName("Strumpfspar");
    bankAccount->save();
    delete bankAccount;

    membermanager::entity::Contribution *contribution = new membermanager::entity::Contribution();
    contribution->setMemberId(1);
    contribution->setFee(15.0);
    contribution->setDonation(10.0);
    contribution->setAdditionalDonation(3.0);
    contribution->setAdditionalFee(2.0);
    contribution->setAmortization(8.0);
    contribution->setValidFrom(QDate(2013, 8, 1));
    contribution->save();
    delete contribution;

}

void AccountingHandlerTest::testGetAccountingData()
{
    QFAIL("TODO  ......");
}

void AccountingHandlerTest::testBook()
{
    QSettings settings;
    settings.setValue("bank/name", QString("foobar"));
    settings.setValue("bank/code", QString("39912399"));
    settings.setValue("bank/account", QString("123456"));

    membermanager::accounting::MemberAccountingData accountingData;
    accountingData.setAccountingInfo("foo");
    accountingData.setPurpose("bar");
    accountingData.setAdditionalDonation(3.0);
    accountingData.setAdditionalFee(2.0);
    accountingData.setAmortization(8.0);
    accountingData.setBankAccountNumber("22334455");
    accountingData.setBankCode("80070099");
    accountingData.setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData.setDonation(10.0);
    accountingData.setFee(15.0);
    accountingData.setFirstname("James T.");
    accountingData.setMemberId("1");
    accountingData.setName("Kirk");
    accountingData.setValuta(QDate(2013, 9, 29));

    QList<QObject *> accountingList;
    accountingList.append(&accountingData);


    membermanager::gui::AccountingHandler handler;

    handler.setAccountingDataList(accountingList);

    handler.book("testfile");

    QFile file("testfile.csv");
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream stream(&file);
    QCOMPARE(stream.readLine(), QString("29.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag Kirk, James T.;15"));

    file.close();

    QFile file2("testfile.txt");
    QVERIFY(file2.open(QIODevice::ReadOnly | QIODevice::Text));

    QTextStream stream2(&file2);

    QString line = stream2.readLine();

    QRegExp regExp(".*BAR BEITRAG 15EUR SPENDE 101  0102EUR CCC 5EUR RATE 8EUR.*");
    QVERIFY(regExp.exactMatch(line));

    file2.close();

    QDjangoQuerySet<membermanager::entity::Balance> result;
    QCOMPARE(result.size(), 10);
    QList<QVariantMap> propertyMaps = result.values(QStringList() << "value" << "purpose");
    QVariantMap property = propertyMaps.at(0);
    QCOMPARE(property["value"], QVariant(-15.0));
    QCOMPARE(property["purpose"], QVariant("Mitgliedsbeitrag foo"));
}

}
}

QTEST_MAIN(test::gui::AccountingHandlerTest)
#include "moc_accountinghandlertest.cpp"

