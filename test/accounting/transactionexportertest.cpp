
#include <QtTest/QtTest>

#include <QDate>
#include <QTextStream>
#include <QSharedDataPointer>

#include "testconfig.h"

#include "dtaus/transaction.h"
#include "dtaus/exporter.h"

#include "sepa/transaction.h"
#include "sepa/exporter.h"

#include "accounting/memberaccountingdata.h"

#include "accounting/transactionexporter.h"

namespace test {
namespace accounting {

class TransactionExporterTest : public QObject
{
    Q_OBJECT

private slots:
    void testAddTransaction();
};

void TransactionExporterTest::testAddTransaction()
{
    membermanager::accounting::MemberAccountingData* accountingData = new membermanager::accounting::MemberAccountingData();

    membermanager::accounting::TransactionExporter exporter("creditorId", "iban", "bic", "name", "account", "bankName", "bankCode");

    exporter.addTransaction(accountingData);

    QString sepaData;
    QTextStream sepaStream;
    sepaStream.setString(&sepaData);

    QString dtausData;
    QTextStream dtausStream;
    dtausStream.setString(&dtausData);

    QString transactionData;
    QTextStream transactionStream;
    transactionStream.setString(&transactionData);

    exporter.out(sepaStream, dtausStream, transactionStream);

    //QCOMPARE(sepaData, QString(""));
    //QCOMPARE(dtausData, QString(""));
    //QCOMPARE(transactionData, QString(""));
}

}
}

QTEST_MAIN(test::accounting::TransactionExporterTest)
#include "moc_transactionexportertest.cpp"



