#ifndef MEMBERMANAGER_DAO_CASHACCOUNTDAO_H
#define MEMBERMANAGER_DAO_CASHACCOUNTDAO_H

#include <QVariant>
#include <QList>
#include <QTableWidget>

#include "swift/transaction.h"
#include "dao/memberdao.h"

namespace membermanager
{
namespace dao
{

class CashAccountDao
{
public:
    CashAccountDao();

    bool importTransactions(QList<qiabanking::swift::Transaction *> aTransactionList);
    bool addTransaction(QTableWidget *aTable);

private:
    MemberDao memberDao;

    QTableWidgetItem *createItem(QVariant aVariant);
    QTableWidgetItem *createEditableItem(QVariant aVariant);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CASHACCOUNTDAO_H
