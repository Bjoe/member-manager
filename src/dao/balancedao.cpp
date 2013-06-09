#include "balancedao.h"

#include "dao/databasestructure.h"

namespace membermanager {
namespace dao {

BalanceDao::BalanceDao(const QSqlDatabase &aDatabase, QObject *aParent) : model(new QSqlTableModel(aParent, aDatabase))
{
    model->setTable(BalanceTable::TABLENAME);
    model->setObjectName(BalanceTable::TABLENAME);
}

bool BalanceDao::saveRecord(const accounting::BalanceEntry &anEntry)
{
    QSqlRecord record = anEntry.balanceRecord;

    bool successful = model->insertRecord(-1, record);
    printSqlError(model->lastError());
    return successful;
}

QList<accounting::BalanceEntry> BalanceDao::findByMemberId(int aMemberId)
{
    QString columnnameId = BalanceTable::COLUMNNAME[BalanceTable::dorfmitglied_pkey];
    QString filter = QString("%1 = %2").arg(columnnameId).arg(aMemberId);
    model->setFilter(filter);
    model->setSort(BalanceTable::datum, Qt::DescendingOrder);
    model->select();

    QList<accounting::BalanceEntry> entryList;
    int row = 0;
    do {
        model->fetchMore();

        for(; row < model->rowCount(); row++) {
            accounting::BalanceEntry entry(aMemberId);
            entry.balanceRecord = model->record(row);
            entryList.append(entry);
        }
    }
    while(model->canFetchMore());

    return entryList;
}

QList<accounting::BalanceEntry> BalanceDao::findContributionByMemberIdAndYear(int aMemberId, int aYear)
{
    QString columnnameId = BalanceTable::COLUMNNAME[BalanceTable::dorfmitglied_pkey];
    QString memberFilter = QString("%1 = %2").arg(columnnameId).arg(aMemberId);

    QString columnnameType = BalanceTable::COLUMNNAME[BalanceTable::konten];
    QString typeFilter = QString("(%1 = 11 OR %1 = 12)").arg(columnnameType);

    /*
      I think SQL sucks
    QString columnnameValuta = BalanceTable::COLUMNNAME[BalanceTable::datum];
    QString valutaFilter = QString("%1 BETWEEN to_date('01.01.%2', 'DD.MM.YYYY') AND to_date('31.12.%2', 'DD.MM.YYYY')")
            .arg(columnnameValuta).arg(aYear);
    */

    QString filter = QString("%1 AND %2").arg(memberFilter).arg(typeFilter);

    model->setFilter(filter);
    model->setSort(BalanceTable::datum, Qt::AscendingOrder);
    model->select();
    printSqlError(model->lastError());

    QList<accounting::BalanceEntry> entryList;
    int row = 0;
    do {
        model->fetchMore();

        for(; row < model->rowCount(); row++) {
            accounting::BalanceEntry entry(aMemberId);
            entry.balanceRecord = model->record(row);
            int year = entry.getValuta().year();
            if(year == aYear) {
                entryList.append(entry);
            }
        }
    }
    while(model->canFetchMore());

    return entryList;
}

QSqlTableModel* BalanceDao::getModelByMemberId(int aMemberId)
{
    model->setHeaderData(BalanceTable::betrag, Qt::Horizontal, model->tr("Betrag"));
    model->setHeaderData(BalanceTable::datum, Qt::Horizontal, model->tr("Valuta Datum"));
    model->setHeaderData(BalanceTable::bezeichnung, Qt::Horizontal, model->tr("Bezeichnung"));
    model->removeColumn(BalanceTable::barkonto);
    model->setHeaderData(BalanceTable::konten -1, Qt::Horizontal, model->tr("Konten"));
    model->setHeaderData(BalanceTable::kasse_pkey -1, Qt::Horizontal, model->tr("Kassa Id"));
    model->setHeaderData(BalanceTable::info -1, Qt::Horizontal, model->tr("Info"));

    QString columnnameId = BalanceTable::COLUMNNAME[BalanceTable::dorfmitglied_pkey];
    QString filterId = QString("%1 = %2").arg(columnnameId).arg(aMemberId);
    model->setFilter(filterId);
    model->setSort(BalanceTable::datum, Qt::DescendingOrder);
    model->select();

    return model;
}

QModelIndex BalanceDao::insertNewEmptyRowWithMemberId(int aMemberId)
{
    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row, BalanceTable::dorfmitglied_pkey), aMemberId);
    model->submitAll();
    printSqlError(model->lastError());
    return model->index(row, BalanceTable::betrag);
}

bool BalanceDao::deleteRow(const QModelIndex &anIndex)
{
    bool successful = model->removeRow(anIndex.row());
    printSqlError(model->lastError());
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
