#ifndef MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H
#define MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H

#include <QString>
#include <QDate>
#include <QList>
#include <QSharedPointer>

#include "entity/balance.h"

#include "accounting/memberaccountingdata.h"

namespace membermanager {
namespace accounting {

class AccountTransaction
{
public:
    AccountTransaction();

    void collectionAccounting(const MemberAccountingData* accountingData);
    void accounting(const MemberAccountingData* accountingData);
    void commit();

private:
    QList<entity::Balance *> m_balanceList;

    void createAndSaveBalance(const MemberAccountingData* accountingData, int account, double value, const QString &purpose, const QString &info);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_ACCOUNTTRANSACTION_H
