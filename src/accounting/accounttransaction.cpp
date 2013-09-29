#include "accounttransaction.h"

#include "dtaus/transactionbuilder.h"

#include "entity/bankaccount.h"
#include "entity/contribution.h"
#include "entity/balance.h"

#include "dao/contributiontablemodel.h"
#include "dao/bankaccounttablemodel.h"

namespace membermanager {
namespace accounting {

AccountTransaction::AccountTransaction(const QString &accountNumber, const QString &bankCode, const QString &bankName, QTextStream &stream)
    : m_accountNumber(accountNumber), m_bankCode(bankCode), m_bankName(bankName), m_stream(stream)
{
}

qiabanking::dtaus::Transaction AccountTransaction::createDtausTransaction(const MemberAccountingData &memberData, const QString &purpose)
{
    QVariant memberId = memberData.memberId();
    QString name = memberData.name();
    QString firstname = memberData.firstname();
    QString accountNumber = memberData.bankAccountNumber();
    QString bankCode = memberData.bankCode();
    double fee = memberData.fee();
    double donation = memberData.donation();
    double additionalFee = memberData.additionalFee();
    double additionalDonation = memberData.additionalDonation();
    double amortization = memberData.amortization();
    QDate date = memberData.date();

    double value = fee + donation + additionalFee + additionalDonation + amortization;

    QString remoteName = QString("%1, %2").arg(name).arg(firstname);

    QString info = QString("%1 Beitrag %L2EUR")
            .arg(purpose)
            .arg(fee);
    m_stream << QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag %2;%3\n")
                .arg(date.toString("dd.MM.yyyy"))
                .arg(remoteName)
                .arg(fee);
    if(donation > 0) {
        info.append(QString(" Spende %L1EUR")
                       .arg(donation));
        m_stream << QString("%1;Lastschrift Einzug 012;012 Spende %2;%3\n")
                    .arg(date.toString("dd.MM.yyyy"))
                    .arg(remoteName)
                    .arg(donation);
    }
    if(additionalDonation + additionalFee > 0) {
        info.append(QString(" CCC %L1EUR")
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
        info.append(QString(" Rate %L1EUR")
                       .arg(amortization));
        m_stream << QString("%1;Lastschrift Einzug 011;011 Mitgliedsbeitrag Rate %2;%3\n")
                    .arg(date.toString("dd.MM.yyyy"))
                    .arg(remoteName)
                    .arg(additionalFee);
    }

    qiabanking::dtaus::Transaction transaction = qiabanking::dtaus::TransactionBuilder()
            .withLocalName(m_bankName)
            .withLocalAccountNumber(m_accountNumber)
            .withLocalBankCode(m_bankCode)
            .withRemoteName(remoteName)
            .withRemoteAccountNumber(accountNumber)
            .withRemoteBankCode(bankCode)
            .withValue(value)
            .withTextKey(5)
            .withPurpose(info)
            .build();

    return transaction;
}

void AccountTransaction::collectionAccounting(const MemberAccountingData &memberData, const QString &purpose)
{
    QVariant memberId = memberData.memberId();
    double fee = memberData.fee();
    double donation = memberData.donation();
    double additionalFee = memberData.additionalFee();
    double additionalDonation = memberData.additionalDonation();
    double amortization = memberData.amortization();
    QDate date = memberData.date();

    createAndSaveBalance(
                memberId,
                date,
                11,
                fee,
                QString("Mitgliedsbeitrag %1").arg(purpose),
                "Automatische Monats Lastschrift");

    if(donation > 0) {
        createAndSaveBalance(
                    memberId,
                    date,
                    12,
                    donation,
                    QString("Spende %1").arg(purpose),
                    "Automatische Monats Lastschrift");
    }

    if(additionalDonation > 0) {
        createAndSaveBalance(
                    memberId,
                    date,
                    4,
                    additionalFee,
                    QString("CCC Beitrag %1").arg(purpose),
                    "Automatische Monats Lastschrift");

        createAndSaveBalance(
                    memberId,
                    date,
                    3,
                    additionalDonation,
                    QString("CCC Spende %1").arg(purpose),
                    "Automatische Monats Lastschrift");
    }

    if(amortization > 0) {
        createAndSaveBalance(
                    memberId,
                    date,
                    2,
                    amortization,
                    QString("Rate %1").arg(purpose),
                    "Automatische Monats Lastschrift");
    }
}

void AccountTransaction::accounting(const MemberAccountingData &memberData, const QString &purpose)
{
    QVariant memberId = memberData.memberId();
    double fee = memberData.fee();
    double donation = memberData.donation();
    double additionalFee = memberData.additionalFee();
    double additionalDonation = memberData.additionalDonation();
    double amortization = memberData.amortization();
    QDate date = memberData.date();

    createAndSaveBalance(
                memberId,
                date,
                -11,
                fee * -1,
                QString("Mitgliedsbeitrag %1").arg(purpose),
                "Automatische Monats Abbuchung");

    if(donation > 0) {
        createAndSaveBalance(
                    memberId,
                    date,
                    -12,
                    donation * -1,
                    QString("Spende %1").arg(purpose),
                    "Automatische Monats Abbuchung");
    }

    if(additionalDonation > 0) {
        createAndSaveBalance(
                    memberId,
                    date,
                    -4,
                    additionalFee * -1,
                    QString("CCC Beitrag %1").arg(purpose),
                    "Automatische Monats Abbuchung");

        createAndSaveBalance(
                    memberId,
                    date,
                    -3,
                    additionalDonation * -1,
                    QString("CCC Spende %1").arg(purpose),
                    "Automatische Monats Abbuchung");
    }

    if(amortization > 0) {

        createAndSaveBalance(
                    memberId,
                    date,
                    -2,
                    amortization * -1,
                    QString("Rate %1").arg(purpose),
                    "Automatische Monats Abbuchung");
    }
}

void AccountTransaction::createAndSaveBalance(
        const QVariant& memberId,
        const QDate& valuta,
        int account,
        double value,
        const QString& purpose,
        const QString& info
        )
{
    int id = memberId.toInt();
    entity::Balance* balance = new entity::Balance();
    balance->setMemberId(id);
    balance->setValue(value);
    balance->setValuta(valuta);
    balance->setAccount(account);
    balance->setPurpose(purpose);
    balance->setInfo(info);
    balance->save();
    delete balance;
}

} // namespace accounting
} // namespace membermanager
