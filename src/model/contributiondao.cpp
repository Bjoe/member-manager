#include "contributiondao.h"

#include "model/databasestructure.h"

namespace membermanager {
namespace model {

ContributionDao::ContributionDao(const QSqlDatabase &aDatabase) : database(aDatabase)
{
}

bool ContributionDao::saveRecord(const accounting::ContributionEntry &anEntry)
{
    QSqlRecord record = anEntry.contributionRecord;

    QSqlTableModel model(0, database);
    model.setTable(ContributionTable::TABLENAME);

    bool successful = model.insertRecord(-1, record);
    printSqlError(model.lastError());
    return successful;
}

void ContributionDao::printSqlError(const QSqlError &anError)
{
    if (anError.type() != QSqlError::NoError) {
        /// \todo Publish error to the statusbar as event.
        qDebug() << anError.text();
    }
}

} // namespace model
} // namespace membermanager
