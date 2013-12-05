#include "transactioncreator.h"

#include "dtaus/transactionbuilder.h"

namespace membermanager {
namespace accounting {

TransactionCreator::TransactionCreator(QString accountNumber, QString bankCode, QString bankName, QString name, QString creditorId, QString iban, QString bic)
    : m_accountNumber{accountNumber}, m_bankCode{bankCode}, m_bankName{bankName}, m_name{name}, m_creditorId{creditorId}, m_iban{iban}, m_bic{bic}, m_transaction{}
{

}

qaqbanking::dtaus::TransactionPtr TransactionCreator::createDtausTransaction(const MemberAccountingData *memberData)
{
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
    if(donation > 0) {
        purpose.append(QString(" Spende %L1EUR")
                       .arg(donation));
    }
    if(additionalDonation + additionalFee > 0) {
        purpose.append(QString(" CCC %L1EUR")
                       .arg(additionalDonation + additionalFee));
    }
    if(amortization > 0) {
        purpose.append(QString(" Rate %L1EUR")
                       .arg(amortization));
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

qaqbanking::sepa::TransactionPtr TransactionCreator::createTransaction(const MemberAccountingData *accountingData)
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

    // TODO in prepare Accounting auslagern
    purpose.append(QString(" Beitrag %L2EUR")
            .arg(fee));

    m_transaction.append(QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag %3 %2 %4;%5\n")
                .arg(valuta.toString("dd.MM.yyyy"))
                .arg(memberId)
                .arg(accountingReference)
                .arg(remoteName)
                .arg(fee));
    if(donation > 0) {
        // TODO in prepare Accounting auslagern
        purpose.append(QString(" Spende %L1EUR")
                       .arg(donation));

    m_transaction.append(QString("%1;Lastschrift Einzug 012;012 Spende %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(donation));
    }
    if(additionalDonation + additionalFee > 0) {
        // TODO in prepare Accounting auslagern
        purpose.append(QString(" CCC %L1EUR")
                       .arg(additionalDonation + additionalFee));

        m_transaction.append(QString("%1;Lastschrift Einzug 004;004 Durchlaufender Posten / CCC Beitrag %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(additionalFee));
        m_transaction.append(QString("%1;Lastschrift Einzug 005;005 Durchlaufender Posten / CCC Spende %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(additionalDonation));
    }
    if(amortization > 0) {
        // TODO in prepare Accounting auslagern
        purpose.append(QString(" Rate %L1EUR")
                       .arg(amortization));

        m_transaction.append(QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag Rate %3 %2 %4;%5\n")
                    .arg(valuta.toString("dd.MM.yyyy"))
                    .arg(memberId)
                    .arg(accountingReference)
                    .arg(remoteName)
                    .arg(amortization));
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

void TransactionCreator::out(QTextStream &stream)
{
    stream << m_transaction;
}

} // namespace accounting
} // namespace membermanager
