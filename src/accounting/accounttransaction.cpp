#include "accounttransaction.h"

#include "dtaus/transactionbuilder.h"

#include "entity/bankaccount.h"
#include "entity/contribution.h"
#include "entity/balance.h"

#include "dao/contributiontablemodel.h"
#include "dao/bankaccounttablemodel.h"

namespace membermanager {
namespace accounting {

AccountTransaction::AccountTransaction(QString accountNumber, QString bankCode, QString bankName, QString name, QString creditorId, QString iban, QString bic, QTextStream& stream)
    : m_accountNumber{accountNumber}, m_bankCode{bankCode}, m_bankName{bankName}, m_name{name}, m_creditorId{creditorId}, m_iban{iban}, m_bic{bic}, m_stream{stream}
{
}

qaqbanking::dtaus::TransactionPtr AccountTransaction::createDtausTransaction(const MemberAccountingData* memberData)
{
    QVariant memberId = memberData->memberId();
    QString name = memberData->name();
    QString firstname = memberData->firstname();
    QString accountNumber = memberData->bankAccountNumber();
    QString bankCode = memberData->bankCode();
    double fee = memberData->fee();
    double donation = memberData->donation();
    double additionalFee = memberData->additionalFee();
    double additionalDonation = memberData->additionalDonation();
    double amortization = memberData->amortization();
    QDate date = memberData->valuta();
    QString purpose = memberData->purpose();

    QString remoteName = QString("%1, %2").arg(name).arg(firstname);

    purpose.append(QString(" Beitrag %L2EUR")
            .arg(fee));
    m_stream << QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag %2;%3\n")
                .arg(date.toString("dd.MM.yyyy"))
                .arg(remoteName)
                .arg(fee);
    if(donation > 0) {
        purpose.append(QString(" Spende %L1EUR")
                       .arg(donation));
        m_stream << QString("%1;Lastschrift Einzug 012;012 Spende %2;%3\n")
                    .arg(date.toString("dd.MM.yyyy"))
                    .arg(remoteName)
                    .arg(donation);
    }
    if(additionalDonation + additionalFee > 0) {
        purpose.append(QString(" CCC %L1EUR")
                       .arg(additionalDonation + additionalFee));
        m_stream << QString("%1;Lastschrift Einzug 004;004 Durchlaufender Posten / CCC Beitrag %2;%3\n")
                    .arg(date.toString("dd.MM.yyyy"))
                    .arg(remoteName)
                    .arg(additionalFee);
        m_stream << QString("%1;Lastschrift Einzug 005;005 Durchlaufender Posten / CCC Spende %2;%3\n")
                    .arg(date.toString("dd.MM.yyyy"))
                    .arg(remoteName)
                    .arg(additionalDonation);
    }
    if(amortization > 0) {
        purpose.append(QString(" Rate %L1EUR")
                       .arg(amortization));
        m_stream << QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag Rate %2;%3\n")
                    .arg(date.toString("dd.MM.yyyy"))
                    .arg(remoteName)
                    .arg(amortization);
    }

    qaqbanking::dtaus::TransactionPtr transaction = qaqbanking::dtaus::TransactionBuilder()
            .withLocalName(m_bankName)
            .withLocalAccountNumber(m_accountNumber)
            .withLocalBankCode(m_bankCode)
            .withRemoteName(remoteName)
            .withRemoteAccountNumber(accountNumber)
            .withRemoteBankCode(bankCode)
            .withValue(fee + donation + additionalFee + additionalDonation + amortization)
            .withTextKey(5)
            .withPurpose(purpose)
            .build();

    return transaction;
}

qaqbanking::sepa::TransactionPtr AccountTransaction::createSepaTransaction(const MemberAccountingData *accountingData)
{
    QString remoteName = QString("%1, %2")
            .arg(accountingData->firstname())
            .arg(accountingData->name());
    QString memberId = accountingData->memberId();
    double fee = accountingData->fee();
    double donation = accountingData->donation();
    double additionalFee = accountingData->additionalFee();
    double additionalDonation = accountingData->additionalDonation();
    double amortization = accountingData->amortization();
    QDate valuta = accountingData->valuta();
    QString purpose = accountingData->purpose();
    QString accountingReference = accountingData->accountingReference();

    purpose.append(QString(" Beitrag %L2EUR")
            .arg(fee));
    m_stream << QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag %3 %2 %4;%5\n")
                .arg(valuta.toString("dd.MM.yyyy"))
                .arg(memberId)
                .arg(accountingReference)
                .arg(remoteName)
                .arg(fee);
    if(donation > 0) {
        purpose.append(QString(" Spende %L1EUR")
                       .arg(donation));
        m_stream << QString("%1;Lastschrift Einzug 012;012 Spende %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(donation);
    }
    if(additionalDonation + additionalFee > 0) {
        purpose.append(QString(" CCC %L1EUR")
                       .arg(additionalDonation + additionalFee));
        m_stream << QString("%1;Lastschrift Einzug 004;004 Durchlaufender Posten / CCC Beitrag %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(additionalFee);
        m_stream << QString("%1;Lastschrift Einzug 005;005 Durchlaufender Posten / CCC Spende %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(additionalDonation);
    }
    if(amortization > 0) {
        purpose.append(QString(" Rate %L1EUR")
                       .arg(amortization));
        m_stream << QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag Rate %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(amortization);
    }

    qaqbanking::sepa::TransactionPtr transaction = qaqbanking::sepa::TransactionPtr(new qaqbanking::sepa::Transaction());
    transaction->setLocalName(m_name);
    transaction->setLocalIban(m_iban);
    transaction->setLocalBic(m_bic);
    transaction->setCreditiorSchemeId(m_creditorId);
    transaction->setRemoteName(remoteName);
    transaction->setRemoteBic(accountingData->sepaBic());
    transaction->setRemoteIban(accountingData->sepaIban());
    // TODO it must be better: Refactor!
    QString type = accountingData->sepaSequenceState();
    if(type == "FIRST") {
        transaction->setSequenceType(qaqbanking::sepa::Transaction::FIRST);
    } else {
        transaction->setSequenceType(qaqbanking::sepa::Transaction::FOLLOWING);
    }
    transaction->setEndToEndReference(accountingReference);
    transaction->setMandateId(memberId);
    transaction->setMandateDate(accountingData->sepaMandateDate());
    transaction->setCollectionDate(valuta);
    transaction->setPurpose(purpose);
    transaction->setValue(fee + donation + additionalFee + additionalDonation + amortization);
    return transaction;
}

void AccountTransaction::collectionAccounting(const MemberAccountingData* accountingData)
{
    QString purpose = accountingData->accountingInfo();

    double fee = accountingData->fee();
    createAndSaveBalance(
                accountingData,
                11,
                fee,
                QString("Mitgliedsbeitrag %1").arg(purpose),
                "Automatische Monats Lastschrift");

    double donation = accountingData->donation();
    if(donation > 0) {
        createAndSaveBalance(
                    accountingData,
                    12,
                    donation,
                    QString("Spende %1").arg(purpose),
                    "Automatische Monats Lastschrift");
    }

    double additionalFee = accountingData->additionalFee();
    double additionalDonation = accountingData->additionalDonation();
    if(additionalDonation + additionalFee > 0) {
        createAndSaveBalance(
                    accountingData,
                    4,
                    additionalFee,
                    QString("CCC Beitrag %1").arg(purpose),
                    "Automatische Monats Lastschrift");

        createAndSaveBalance(
                    accountingData,
                    3,
                    additionalDonation,
                    QString("CCC Spende %1").arg(purpose),
                    "Automatische Monats Lastschrift");
    }

    double amortization = accountingData->amortization();
    if(amortization > 0) {
        createAndSaveBalance(
                    accountingData,
                    2,
                    amortization,
                    QString("Rate %1").arg(purpose),
                    "Automatische Monats Lastschrift");
    }
}

void AccountTransaction::accounting(const MemberAccountingData* accountingData)
{
    QString purpose = accountingData->accountingInfo();

    double fee = accountingData->fee();
    createAndSaveBalance(
                accountingData,
                -11,
                fee * -1,
                QString("Mitgliedsbeitrag %1").arg(purpose),
                "Automatische Monats Abbuchung");

    double donation = accountingData->donation();
    if(donation > 0) {
        createAndSaveBalance(
                    accountingData,
                    -12,
                    donation * -1,
                    QString("Spende %1").arg(purpose),
                    "Automatische Monats Abbuchung");
    }

    double additionalFee = accountingData->additionalFee();
    double additionalDonation = accountingData->additionalDonation();
    if(additionalDonation + additionalFee > 0) {
        createAndSaveBalance(
                    accountingData,
                    -4,
                    additionalFee * -1,
                    QString("CCC Beitrag %1").arg(purpose),
                    "Automatische Monats Abbuchung");

        createAndSaveBalance(
                    accountingData,
                    -3,
                    additionalDonation * -1,
                    QString("CCC Spende %1").arg(purpose),
                    "Automatische Monats Abbuchung");
    }

    double amortization = accountingData->amortization();
    if(amortization > 0) {

        createAndSaveBalance(
                    accountingData,
                    -2,
                    amortization * -1,
                    QString("Rate %1").arg(purpose),
                    "Automatische Monats Abbuchung");
    }
}

void AccountTransaction::createAndSaveBalance(
        const MemberAccountingData* accountingData,
        int account,
        double value,
        const QString& purpose,
        const QString& info
        )
{
    entity::Balance* balance = new entity::Balance();
    balance->setMemberId(accountingData->memberId());
    balance->setValuta(accountingData->valuta());
    balance->setAccountingReference(accountingData->accountingReference());
    balance->setValue(value);
    balance->setAccount(account);
    balance->setPurpose(purpose);
    balance->setInfo(info);
    balance->save();
    delete balance;
}

} // namespace accounting
} // namespace membermanager
