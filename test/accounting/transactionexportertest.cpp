
#include <QtTest/QtTest>

#include <QDate>
#include <QRegExp>
#include <QTextStream>
#include <QSharedDataPointer>

#include "testconfig.h"

#include "dtaus/transaction.h"
#include "dtaus/exporter.h"

#include "sepa/transaction.h"
#include "sepa/exporter.h"

#include "entity/member.h"
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
    accountingData->setAccountingInfo("Test Foo");
    accountingData->setPurpose("Test Bar");
    accountingData->setAdditionalDonation(3.0);
    accountingData->setAdditionalFee(2.0);
    accountingData->setAmortization(8.0);
    accountingData->setBankAccountNumber("22334455");
    accountingData->setBankCode("80070099");
    accountingData->setSepaBic("DUSSDEDDXXX");
    accountingData->setSepaIban("DE26312345670012345678");
    accountingData->setSepaMandateDate(QDate(2013,11,30));
    accountingData->setSepaSequenceState("FIRST");
    accountingData->setAccountingReference("9876543210");
    accountingData->setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData->setDonation(10.0);
    accountingData->setFee(15.0);
    accountingData->setFirstname("James T.");
    accountingData->setMemberId("1");
    accountingData->setName("Kirk");
    accountingData->setValuta(QDate(2013, 9, 29));

    membermanager::accounting::MemberAccountingData* accountingData2 = new membermanager::accounting::MemberAccountingData();
    accountingData2->setAccountingInfo("Test Foo");
    accountingData2->setPurpose("Test Bar");
    accountingData2->setAdditionalDonation(3.0);
    accountingData2->setAdditionalFee(2.0);
    accountingData2->setAmortization(8.0);
    accountingData2->setBankAccountNumber("22334455");
    accountingData2->setBankCode("80070099");
    accountingData2->setSepaBic("DUSSDEDDXXX");
    accountingData2->setSepaIban("DE26312345670012345678");
    accountingData2->setSepaMandateDate(QDate(2013,11,30));
    accountingData2->setSepaSequenceState("FOLLOW");
    accountingData2->setAccountingReference("9876543210");
    accountingData2->setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));
    accountingData2->setDonation(10.0);
    accountingData2->setFee(15.0);
    accountingData2->setFirstname("James T.");
    accountingData2->setMemberId("1");
    accountingData2->setName("Kirk");
    accountingData2->setValuta(QDate(2013, 9, 29));

    QString sepaDataFirst;
    QTextStream sepaStreamFirst;
    sepaStreamFirst.setString(&sepaDataFirst);

    QString sepaData;
    QTextStream sepaStream;
    sepaStream.setString(&sepaData);

    QString dtausData;
    QTextStream dtausStream;
    dtausStream.setString(&dtausData);

    QString transactionData;
    QTextStream transactionStream;
    transactionStream.setString(&transactionData);


    membermanager::accounting::TransactionExporter exporter("creditorId", "iban", "bic", "name", "account", "bankName", "bankCode");
    exporter.addTransaction(accountingData);
    exporter.addTransaction(accountingData2);
    exporter.out(sepaStreamFirst, sepaStream, dtausStream, transactionStream);

    QRegExp regExp(".*<SeqTp>FRST</SeqTp>.*");
    QVERIFY(regExp.exactMatch(sepaDataFirst));

    regExp.setPattern(".*<SeqTp>RCUR</SeqTp>.*");
    QVERIFY(regExp.exactMatch(sepaData));

    regExp.setPattern(".*22334455.*");
    QVERIFY(regExp.exactMatch(dtausData));

    regExp.setPattern(".*29.09.2013;Lastschrift Einzug 011;011 Mitgliedsbeitrag 9876543210 1 James T., Kirk;15.*");
    QVERIFY(regExp.exactMatch(transactionData));
}

}
}

QTEST_MAIN(test::accounting::TransactionExporterTest)
#include "moc_transactionexportertest.cpp"



