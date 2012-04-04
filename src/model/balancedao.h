#ifndef MEMBERMANAGER_MODEL_BALANCEDAO_H
#define MEMBERMANAGER_MODEL_BALANCEDAO_H

#include <QtSql>

#include "accounting/balanceentry.h"

namespace membermanager {
namespace accounting{class BalanceEntry;}

namespace model {

class BalanceDao
{
public:
    BalanceDao(const QSqlDatabase &aDatabase);

    bool saveRecord(const accounting::BalanceEntry &anEntry);

private:
    QSqlDatabase database;

    void printSqlError(const QSqlError &anError);
};

} // namespace model
} // namespace membermanager

#endif // MEMBERMANAGER_MODEL_BALANCEDAO_H
