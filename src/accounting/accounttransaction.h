#ifndef MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H
#define MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H

#include <QString>
#include <QDate>
#include <QTextStream>

#include "dtaus/transaction.h"

#include "entity/member.h"

#include "accounting/memberaccountingdata.h"

namespace membermanager {
namespace accounting {

class AccountTransaction
{
public:
    AccountTransaction(const QString &accountNumber, const QString &bankCode, const QString &bankName, QTextStream& srteam);

    qiabanking::dtaus::Transaction createDtausTransaction(const MemberAccountingData &memberData, QString &purpose);
    void collectionAccounting(const MemberAccountingData &memberData, QString &purpose);
    void accounting(const MemberAccountingData &memberData, QString &purpose);

private:
    QString m_accountNumber;
    QString m_bankCode;
    QString m_bankName;
    QTextStream& m_stream;

    void createAndSaveBalance(const QVariant &memberId, const QDate &valuta, int account, double value, const QString &purpose, const QString &info);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H
