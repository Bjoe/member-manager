#include "contributiondao.h"

#include "model/databasestructure.h"

namespace membermanager {
namespace model {

ContributionDao::ContributionDao(const QSqlDatabase &aDatabase) : model(0, aDatabase)
{
    model.setTable(ContributionTable::TABLENAME);
}

bool ContributionDao::saveRecord(const accounting::ContributionEntry &anEntry)
{
    QSqlRecord record = anEntry.contributionRecord;

    bool successful = model.insertRecord(-1, record);
    printSqlError(model.lastError());
    return successful;
}

accounting::ContributionEntry ContributionDao::findByMemberIdWithPointInTime(int anId, const QDate &aDate)
{
    QString columnnameId = model::ContributionTable::COLUMNNAME[model::ContributionTable::MemberId];
    QString filterId = QString("%1 = %2").arg(columnnameId).arg(anId);
    QString columnnameDate = model::ContributionTable::COLUMNNAME[model::ContributionTable::ValidFrom];
    QString filterDate = QString("%1 <= '%2'").arg(columnnameDate).arg(aDate.toString(Qt::ISODate));
    QString filter = QString("%1 AND %2").arg(filterId).arg(filterDate);
    model.setFilter(filter);
    model.setSort(model::ContributionTable::ValidFrom, Qt::DescendingOrder);
    model.select();

    accounting::ContributionEntry entry(anId);
    entry.contributionRecord = model.record(0);
    return entry;
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
