
#include <QtTest/QtTest>

#include <QDate>
#include <QByteArray>
#include <QBuffer>
#include <QTextStream>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSharedDataPointer>

#include "QDjango.h"
#include "QDjangoWhere.h"
#include "QDjangoQuerySet.h"

#include "testconfig.h"

#include "dtaus/transaction.h"
#include "dtaus/exporter.h"

#include "sepa/transaction.h"
#include "sepa/exporter.h"

#include "entity/member.h"
#include "entity/contribution.h"
#include "entity/bankaccount.h"
#include "entity/sepaaccount.h"
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
    void testCreateSepaTransaction();
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
    QDjango::registerModel<membermanager::entity::Balance>();

    QDjango::dropTables();
    QDjango::createTables();
}

void AccountTransactionTest::testCreateTranaction()
{
    membermanager::accounting::MemberAccountingData accountingData;
    accountingData.setMemberId("1");
    accountingData.setFirstname("James T.");
    accountingData.setName("Kirk");
    accountingData.setFee(15.0);
    accountingData.setDonation(10.0);
    accountingData.setAdditionalDonation(3.0);
    accountingData.setAdditionalFee(2.0);
    accountingData.setAmortization(8.0);
    accountingData.setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData.setBankAccountNumber("22334455");
    accountingData.setBankCode("80070099");
    accountingData.setAccountingInfo("foo");
    accountingData.setPurpose("Buchen");
    accountingData.setValuta(QDate(2013, 9, 21));

    QString data;
    QTextStream stream;
    stream.setString(&data);

    membermanager::accounting::AccountTransaction accountTransaction("123456789", "76543210", "Sparstrumpf",
                                                                     "foobar e.V.", "DE202300000782585", "DE26300501100021057476", "DUSSDEDDXXX", stream);

    QSharedPointer<qaqbanking::dtaus::Transaction> transaction = accountTransaction.createDtausTransaction(&accountingData);

    QCOMPARE(data, QString("21.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag Kirk, James T.;15\n"
                           "21.09.2013;Lastschrift Einzug 012;012 Spende Kirk, James T.;10\n"
                           "21.09.2013;Lastschrift Einzug 004;004 Durchlaufender Posten / CCC Beitrag Kirk, James T.;2\n"
                           "21.09.2013;Lastschrift Einzug 005;005 Durchlaufender Posten / CCC Spende Kirk, James T.;3\n"
                           "21.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag Rate Kirk, James T.;8\n"));

    QCOMPARE(transaction->localName(), QString("Sparstrumpf"));
    QCOMPARE(transaction->localBankCode(), QString("76543210"));
    QCOMPARE(transaction->localAccountNumber(), QString("123456789"));
    QCOMPARE(transaction->remoteName(), QString("Kirk, James T."));
    QCOMPARE(transaction->purpose(), QString("Buchen Beitrag 15EUR Spende 10EUR CCC 5EUR Rate 8EUR"));
    QCOMPARE(transaction->remoteBankCode(), QString("80070099"));
    QCOMPARE(transaction->remoteAccountNumber(), QString("22334455"));
    QCOMPARE(transaction->value(), 38.0);
}

void AccountTransactionTest::testCreateSepaTransaction()
{
    membermanager::accounting::MemberAccountingData* accountingData = new membermanager::accounting::MemberAccountingData();
    accountingData->setAccountingInfo("foo");
    accountingData->setPurpose("Buchen");
    accountingData->setAdditionalDonation(3.0);
    accountingData->setAdditionalFee(2.0);
    accountingData->setAmortization(8.0);
    accountingData->setSepaBic("DUSSDEDDXXX");
    accountingData->setSepaIban("DE26312345670012345678");
    accountingData->setSepaMandateDate(QDate(2013,11,30));
    accountingData->setSepaSequenceState("FIRST");
    accountingData->setAccountingReference("2342");
    accountingData->setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData->setDonation(10.0);
    accountingData->setFee(15.0);
    accountingData->setFirstname("James T.");
    accountingData->setMemberId("23");
    accountingData->setName("Kirk");
    accountingData->setValuta(QDate(2013, 9, 29));

    QString data;
    QTextStream stream;
    stream.setString(&data);

    membermanager::accounting::AccountTransaction accountTransaction("123456789", "76543210", "Sparstrumpf",
                                                                     "foobar e.V.", "DE202300000782585", "DE26300501100021057476", "DUSSDEDDXXX", stream);

    qaqbanking::sepa::TransactionPtr transaction = accountTransaction.createSepaTransaction(accountingData);

    QCOMPARE(data, QString("29.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag 2342 23 James T., Kirk;15\n"
                           "29.09.2013;Lastschrift Einzug 012;012 Spende 2342 23 James T., Kirk;10\n"
                           "29.09.2013;Lastschrift Einzug 004;004 Durchlaufender Posten / CCC Beitrag 2342 23 James T., Kirk;2\n"
                           "29.09.2013;Lastschrift Einzug 005;005 Durchlaufender Posten / CCC Spende 2342 23 James T., Kirk;3\n"
                           "29.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag Rate 2342 23 James T., Kirk;8\n"));

    QCOMPARE(transaction->localName(), QString("foobar e.V."));
    QCOMPARE(transaction->localIban(), QString("DE26300501100021057476"));
    QCOMPARE(transaction->localBic(), QString("DUSSDEDDXXX"));
    QCOMPARE(transaction->remoteName(), QString("James T., Kirk"));
    QCOMPARE(transaction->purpose(), QString("Buchen Beitrag 15EUR Spende 10EUR CCC 5EUR Rate 8EUR"));
    QCOMPARE(transaction->remoteBic(), QString("DUSSDEDDXXX"));
    QCOMPARE(transaction->remoteIban(), QString("DE26312345670012345678"));
    QCOMPARE(transaction->creditorSchemeId(), QString("DE202300000782585"));
    QCOMPARE(transaction->mandateId(), QString("23"));
    QCOMPARE(transaction->mandateDate(), QDate(2013,11,30));
    QCOMPARE(transaction->endToEndReference(), QString("2342"));
    QCOMPARE(transaction->sequenceType(), qaqbanking::sepa::Transaction::FIRST);
    QCOMPARE(transaction->value(), 38.0);
}

void AccountTransactionTest::testBooked()
{
    membermanager::accounting::MemberAccountingData accountingData;
    accountingData.setMemberId("1");
    accountingData.setFirstname("James T.");
    accountingData.setName("Kirk");
    accountingData.setFee(15.0);
    accountingData.setDonation(10.0);
    accountingData.setAdditionalDonation(3.0);
    accountingData.setAdditionalFee(2.0);
    accountingData.setAmortization(8.0);
    accountingData.setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData.setBankAccountNumber("22334455");
    accountingData.setBankCode("80070099");
    accountingData.setAccountingInfo("foo");
    accountingData.setPurpose("Buchen");
    accountingData.setValuta(QDate(2013, 9, 21));

    QTextStream stream;
    membermanager::accounting::AccountTransaction accountTransaction("123456789", "76543210", "Sparstrumpf",
                                                                     "foobar e.V.", "DE202300000782585", "DE26300501100021057476", "DUSSDEDDXXX", stream);


    accountTransaction.accounting(&accountingData);

    QDjangoQuerySet<membermanager::entity::Balance> result;

    QCOMPARE(result.size(), 5);

    accountTransaction.collectionAccounting(&accountingData);

    result = QDjangoQuerySet<membermanager::entity::Balance>();
    QCOMPARE(result.size(), 10);
}

}
}

QTEST_MAIN(test::accounting::AccountTransactionTest)
#include "moc_accounttransactiontest.cpp"

