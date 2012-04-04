#include "balancedao.h"

#include "model/databasestructure.h"
#include "model/memberfilter.h"

namespace membermanager {
namespace model {

BalanceDao::BalanceDao(const QSqlDatabase &aDatabase) : database(aDatabase)
{
}

bool BalanceDao::saveRecord(const accounting::BalanceEntry &anEntry)
{
    QSqlRecord record = anEntry.balanceRecord;
//    int memberId = record.value(SaldoTable::dorfmitglied_pkey).toInt();

    QSqlTableModel model(0, database);
    model.setTable(SaldoTable::TABLENAME);
//    model.setFilter(MemberFilter::build().withMemberId(memberId).createFilter());
//    model.select();

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
