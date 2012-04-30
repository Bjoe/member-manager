#include "contributiondao.h"

#include "dao/databasestructure.h"

namespace membermanager {
namespace dao {

ContributionDao::ContributionDao(const QSqlDatabase &aDatabase, QObject *aParent) : model(new QSqlTableModel(aParent, aDatabase))
{
    model->setTable(ContributionTable::TABLENAME);
    model->setObjectName(ContributionTable::TABLENAME);
}

bool ContributionDao::saveRecord(const accounting::ContributionEntry &anEntry)
{
    bool successful = false;
    QString primaryKeyName = ContributionTable::COLUMNNAME[ContributionTable::ContributionId];
    QSqlRecord record = anEntry.contributionRecord; 
    if(record.contains(primaryKeyName)) {
        int primaryKey = record.value(primaryKeyName).toInt();
        QString filter = QString("%1 = %2").arg(primaryKeyName).arg(primaryKey);
        model->setFilter(filter);
        model->select();
        model->setRecord(0, record);
        printSqlError(model->lastError());
        successful = model->submitAll();
    } else {
        successful = model->insertRecord(-1, record);
    }
    printSqlError(model->lastError());
    return successful;
}

accounting::ContributionEntry ContributionDao::findByMemberIdWithPointInTime(int aMemberId, const QDate &aDate)
{
    QString columnnameDate = ContributionTable::COLUMNNAME[ContributionTable::ValidFrom];
    QString filterDate = QString("%1 <= '%2'").arg(columnnameDate).arg(aDate.toString(Qt::ISODate));

    QString columnnameId = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    QString filterId = QString("%1 = %2").arg(columnnameId).arg(aMemberId);
    QString filter = QString("%1 AND %2").arg(filterId).arg(filterDate);
    model->setFilter(filter);
    model->setSort(ContributionTable::ValidFrom, Qt::DescendingOrder);
    model->select();

    accounting::ContributionEntry entry(aMemberId);
    entry.contributionRecord = model->record(0);
    return entry;
}

accounting::ContributionEntry ContributionDao::findLastDateByMemberId(int aMemberId)
{
    QString columnnameId = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    QString filterId = QString("%1 = %2").arg(columnnameId).arg(aMemberId);
    model->setFilter(filterId);
    model->setSort(ContributionTable::ValidFrom, Qt::DescendingOrder);
    model->select();

    accounting::ContributionEntry entry(aMemberId);
    entry.contributionRecord = model->record(0);
    return entry;
}

QSqlTableModel* ContributionDao::getModelByMemberId(int aMemberId)
{
    model->setHeaderData(ContributionTable::Fee, Qt::Horizontal, model->tr("Beitrag"));
    model->setHeaderData(ContributionTable::Donation, Qt::Horizontal, model->tr("Spende"));
    model->removeColumn(ContributionTable::Debit);
    model->setHeaderData(ContributionTable::ValidFrom -1, Qt::Horizontal, model->tr("Gueltig ab"));
    model->setHeaderData(ContributionTable::Info -1, Qt::Horizontal, model->tr("Info"));

    QString columnnameId = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    QString filterId = QString("%1 = %2").arg(columnnameId).arg(aMemberId);
    model->setFilter(filterId);
    model->setSort(ContributionTable::ValidFrom -1, Qt::DescendingOrder);
    model->select();

    return model;
}

QModelIndex ContributionDao::insertNewEmptyRowWithMemberId(int aMemberId)
{
    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row, ContributionTable::MemberId), aMemberId);
    model->submitAll();
    printSqlError(model->lastError());
    return model->index(row, ContributionTable::Fee);
}

bool ContributionDao::deleteRow(const QModelIndex &anIndex)
{
    bool successful = model->removeRow(anIndex.row());
    printSqlError(model->lastError());
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
