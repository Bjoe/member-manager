#ifndef MEMBERMANAGER_DAO_BALANCEDAO_H
#define MEMBERMANAGER_DAO_BALANCEDAO_H

#include <QtSql>
#include <QList>

#include "accounting/balanceentry.h"

namespace membermanager {
namespace accounting{class BalanceEntry;}

namespace dao {

class BalanceDao
{
public:
    BalanceDao(const QSqlDatabase &aDatabase = QSqlDatabase::database(), QObject *aParent = 0);

    bool saveRecord(const accounting::BalanceEntry &anEntry);
    QList<accounting::BalanceEntry> findByMemberId(int aMemberId);
    QList<accounting::BalanceEntry> findContributionByMemberIdAndYear(int aMemberId, int aYear);

    QSqlTableModel *getModelByMemberId(int aMemberId);
    QModelIndex insertNewEmptyRowWithMemberId(int aMemberId);
    bool deleteRow(const QModelIndex &anIndex);

private:
    QSqlTableModel *model;

    void printSqlError(const QSqlError &anError);
};

} // namespace model
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_BALANCEDAO_H
