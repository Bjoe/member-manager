
#include <QtTest/QtTest>

#include <QDate>
#include <QByteArray>
#include <QBuffer>
#include <QTextStream>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>

#include "QDjango.h"
#include "QDjangoWhere.h"
#include "QDjangoQuerySet.h"

#include "testconfig.h"

#include <aqbanking/transaction.h>
#include <aqbanking/value.h>
#include <gwenhywfar/stringlist.h>

#include "dtaus/transaction.h"
#include "dtaus/exporter.h"

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/bankaccount.h"
#include "entity/balance.h"

#include "accounting/memberaccountingdata.h"

#include "accounting/accounttransaction.h"

namespace test {
namespace accounting {

class AccountTransactionTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateTranaction();
    void testBooked();
};

void AccountTransactionTest::initTestCase()
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
    QDjango::registerModel<membermanager::entity::Contribution>();
    QDjango::registerModel<membermanager::entity::BankAccount>();
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();

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

void AccountTransactionTest::testCreateTranaction()
{
    membermanager::entity::Member member;
    member.setMemberId(1);
    member.setName("Kirk");
    member.setFirstname("James T.");

    QString data;
    QTextStream stream;
    stream.setString(&data);

    membermanager::accounting::AccountTransaction accountTransaction("123456789", "76543210", "Sparstrumpf", stream);

    membermanager::accounting::MemberAccountingData memberAccounting(&member, QDate(2013, 9, 21));

    QString purpose("Buchen");
    qiabanking::dtaus::Transaction transaction = accountTransaction.createDtausTransaction(memberAccounting, purpose);

    QCOMPARE(data, QString("21.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag Kirk, James T.;15\n"
                           "21.09.2013;Lastschrift Einzug 012;012 Spende Kirk, James T.;10\n"
                           "21.09.2013;Lastschrift Einzug 004;004 Durchlaufender Posten / CCC Beitrag Kirk, James T.;2\n"
                           "21.09.2013;Lastschrift Einzug 005;005 Durchlaufender Posten / CCC Spende Kirk, James T.;3\n"
                           "21.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag Rate Kirk, James T.;2\n"));

    AB_TRANSACTION *abTransaction = transaction.getAbTransaction();
    QCOMPARE(AB_Transaction_GetLocalName(abTransaction), "Sparstrumpf");
    QCOMPARE(AB_Transaction_GetLocalBankCode(abTransaction), "76543210");
    QCOMPARE(AB_Transaction_GetLocalAccountNumber(abTransaction), "123456789");

    const GWEN_STRINGLIST *stringList = AB_Transaction_GetRemoteName(abTransaction);
    unsigned int i = 1;
    QCOMPARE(GWEN_StringList_Count(stringList), i);
    QCOMPARE(GWEN_StringList_StringAt(stringList, 0), "Kirk, James T.");

    const GWEN_STRINGLIST *purposeList = AB_Transaction_GetPurpose(abTransaction);
    QCOMPARE(GWEN_StringList_Count(purposeList), i);
    QCOMPARE(GWEN_StringList_StringAt(purposeList, 0), "Buchen Beitrag 15EUR Spende 10EUR CCC 5EUR Rate 8EUR");

    QCOMPARE(AB_Transaction_GetRemoteBankCode(abTransaction), "80070099");
    QCOMPARE(AB_Transaction_GetRemoteAccountNumber(abTransaction), "22334455");

    const AB_VALUE* value = AB_Transaction_GetValue(abTransaction);
    QCOMPARE(AB_Value_GetValueAsDouble(value), 38.0);
}

void AccountTransactionTest::testBooked()
{
    membermanager::entity::Member member;
    member.setMemberId(1);

    QTextStream stream;
    membermanager::accounting::AccountTransaction accountTransaction("123456789", "76543210", "Sparstrumpf", stream);

    membermanager::accounting::MemberAccountingData memberAccounting(&member, QDate(2013, 9, 21));

    QString purpose("Buchen");

    accountTransaction.accounting(memberAccounting, purpose);

    QDjangoQuerySet<membermanager::entity::Balance> result;

    QCOMPARE(result.size(), 5);

    accountTransaction.collectionAccounting(memberAccounting, purpose);

    result = QDjangoQuerySet<membermanager::entity::Balance>();
    QCOMPARE(result.size(), 10);
}

}
}

QTEST_MAIN(test::accounting::AccountTransactionTest)
#include "moc_accounttransactiontest.cpp"

