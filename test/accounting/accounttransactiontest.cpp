
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

    membermanager::accounting::AccountTransaction accountTransaction;


    accountTransaction.accounting(&accountingData);

    QDjangoQuerySet<membermanager::entity::Balance> result;
    QCOMPARE(result.size(), 0);

    accountTransaction.collectionAccounting(&accountingData);

    result = QDjangoQuerySet<membermanager::entity::Balance>();
    QCOMPARE(result.size(), 0);

    accountTransaction.commit();

    result = QDjangoQuerySet<membermanager::entity::Balance>();
    QCOMPARE(result.size(), 9);
}

}
}

QTEST_MAIN(test::accounting::AccountTransactionTest)
#include "moc_accounttransactiontest.cpp"

