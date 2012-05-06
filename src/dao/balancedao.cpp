#include "balancedao.h"

#include "dao/databasestructure.h"

namespace membermanager {
namespace dao {

BalanceDao::BalanceDao(const QSqlDatabase &aDatabase, QObject *aParent) : model(new QSqlTableModel(aParent, aDatabase))
{
    model->setTable(SaldoTable::TABLENAME);
    model->setObjectName(SaldoTable::TABLENAME);
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
    QString columnnameId = SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey];
    QString filter = QString("%1 = %2").arg(columnnameId).arg(aMemberId);
    model->setFilter(filter);
    model->setSort(SaldoTable::datum, Qt::DescendingOrder);
    model->select();

    QList<accounting::BalanceEntry> entryList;
    for(int row = 0; row < model->rowCount(); row++) {
        accounting::BalanceEntry entry(aMemberId);
        entry.balanceRecord = model->record(row);
        entryList.append(entry);
    }
   return entryList;
}

QList<accounting::BalanceEntry> BalanceDao::findContributionByMemberIdAndYear(int aMemberId, int aYear)
{
    QString columnnameId = SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey];
    QString memberFilter = QString("%1 = %2").arg(columnnameId).arg(aMemberId);

    QString columnnameType = SaldoTable::COLUMNNAME[SaldoTable::konten];
    QString typeFilter = QString("(%1 = 11 OR %1 = 12)").arg(columnnameType);

    /*
      I think SQL sucks
    QString columnnameValuta = SaldoTable::COLUMNNAME[SaldoTable::datum];
    QString valutaFilter = QString("%1 BETWEEN to_date('01.01.%2', 'DD.MM.YYYY') AND to_date('31.12.%2', 'DD.MM.YYYY')")
            .arg(columnnameValuta).arg(aYear);
    */

    QString filter = QString("%1 AND %2").arg(memberFilter).arg(typeFilter);

    model->setFilter(filter);
    model->setSort(SaldoTable::datum, Qt::AscendingOrder);
    model->select();
    printSqlError(model->lastError());

    QList<accounting::BalanceEntry> entryList;
    for(int row = 0; row < model->rowCount(); row++) {
        accounting::BalanceEntry entry(aMemberId);
        entry.balanceRecord = model->record(row);
        int year = entry.getValuta().year();
        if(year == aYear) {
            entryList.append(entry);
        }
   }
   return entryList;
}

QSqlTableModel* BalanceDao::getModelByMemberId(int aMemberId)
{
    model->setHeaderData(SaldoTable::betrag, Qt::Horizontal, model->tr("Betrag"));
    model->setHeaderData(SaldoTable::datum, Qt::Horizontal, model->tr("Valuta Datum"));
    model->setHeaderData(SaldoTable::bezeichnung, Qt::Horizontal, model->tr("Bezeichnung"));
    model->removeColumn(SaldoTable::barkonto);
    model->setHeaderData(SaldoTable::konten -1, Qt::Horizontal, model->tr("Konten"));
    model->setHeaderData(SaldoTable::kasse_pkey -1, Qt::Horizontal, model->tr("Kassa Id"));
    model->setHeaderData(SaldoTable::info -1, Qt::Horizontal, model->tr("Info"));

    QString columnnameId = SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey];
    QString filterId = QString("%1 = %2").arg(columnnameId).arg(aMemberId);
    model->setFilter(filterId);
    model->setSort(SaldoTable::datum, Qt::DescendingOrder);
    model->select();

    return model;
}

QModelIndex BalanceDao::insertNewEmptyRowWithMemberId(int aMemberId)
{
    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row, SaldoTable::dorfmitglied_pkey), aMemberId);
    model->submitAll();
    printSqlError(model->lastError());
    return model->index(row, SaldoTable::betrag);
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
