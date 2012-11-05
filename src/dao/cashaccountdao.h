#ifndef MEMBERMANAGER_DAO_CASHACCOUNTDAO_H
#define MEMBERMANAGER_DAO_CASHACCOUNTDAO_H

#include <QVariant>
#include <QList>
#include <QTableWidget>
#include <QSqlError>

#include "swift/transaction.h"
#include "dao/memberdao.h"
#include "accounting/statemententry.h"

namespace membermanager
{
namespace accounting {class StatementEntry;}
namespace dao
{

class CashAccountDao
{
public:
    CashAccountDao();

    bool importTransactions(QList<qiabanking::swift::Transaction *> aTransactionList);
    bool clearAndAddTransaction(QTableWidget *aTable);
    //bool setBooked(int aKeyId, bool booked);

    bool saveRecord(const accounting::StatementEntry aStatementEntry);
    bool updateRecord(const accounting::StatementEntry aStatementEntry);
    accounting::StatementEntry findById(int aKeyId);

private:
    MemberDao memberDao;

    QTableWidgetItem *createItem(QVariant aVariant);
    QTableWidgetItem *createEditableItem(QVariant aVariant);
    void printSqlError(const QSqlError &anError);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CASHACCOUNTDAO_H
