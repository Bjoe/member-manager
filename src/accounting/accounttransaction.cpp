#include "accounttransaction.h"

#include "dtaus/transactionbuilder.h"

#include "entity/bankaccount.h"
#include "entity/contribution.h"

#include "dao/contributiontablemodel.h"
#include "dao/bankaccounttablemodel.h"

namespace membermanager {
namespace accounting {

AccountTransaction::AccountTransaction() : m_balanceList{}
{
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
}

void AccountTransaction::commit()
{
    for(entity::Balance* balance : m_balanceList) {
        balance->save();
        delete balance;
    }
    m_balanceList.clear();
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
    balance->setMemberId(accountingData->mandateId());
    balance->setValuta(accountingData->valuta());
    balance->setAccountingReference(accountingData->accountingReference());
    balance->setValue(value);
    balance->setAccount(account);
    balance->setPurpose(purpose);
    balance->setInfo(info);

    m_balanceList.append(balance);
}

// TODO commit methode hinzufuegen

} // namespace accounting
} // namespace membermanager
