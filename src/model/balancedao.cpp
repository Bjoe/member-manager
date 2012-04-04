#include "balancedao.h"

#include "model/databasestructure.h"

namespace membermanager {
namespace model {

BalanceDao::BalanceDao(const QSqlDatabase &aDatabase) : database(aDatabase)
{
}

bool BalanceDao::saveRecord(const accounting::BalanceEntry &anEntry)
{
    QSqlRecord record = anEntry.balanceRecord;

    QSqlTableModel model(0, database);
    model.setTable(SaldoTable::TABLENAME);

    bool successful = model.insertRecord(-1, record);
    printSqlError(model.lastError());
    return successful;
}

void BalanceDao::printSqlError(const QSqlError &anError)
{
    if (anError.type() != QSqlError::NoError) {
        /// \todo Publish error to the statusbar as event.
        qDebug() << anError.text();
    }
}

} // namespace model
} // namespace membermanager
