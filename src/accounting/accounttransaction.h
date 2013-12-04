#ifndef MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H
#define MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H

#include <QString>
#include <QDate>
#include <QTextStream>
#include <QSharedPointer>

#include "dtaus/exporter.h"
#include "dtaus/transaction.h"

#include "sepa/exporter.h"
#include "sepa/transaction.h"

#include "entity/member.h"

#include "accounting/memberaccountingdata.h"

namespace membermanager {
namespace accounting {

class AccountTransaction
{
public:
    AccountTransaction(QString accountNumber, QString bankCode, QString bankName,
                       QString name, QString creditorId, QString iban, QString bic, QTextStream& srteam);

    qaqbanking::dtaus::TransactionPtr createDtausTransaction(const MemberAccountingData* memberData);
    qaqbanking::sepa::TransactionPtr createSepaTransaction(const MemberAccountingData* accountingData);
    void collectionAccounting(const MemberAccountingData* accountingData);
    void accounting(const MemberAccountingData* accountingData);

private:
    QString m_accountNumber;
    QString m_bankCode;
    QString m_bankName;
    QString m_name;
    QString m_creditorId;
    QString m_iban;
    QString m_bic;
    QTextStream& m_stream;

    void createAndSaveBalance(const MemberAccountingData* accountingData, int account, double value, const QString &purpose, const QString &info);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H
