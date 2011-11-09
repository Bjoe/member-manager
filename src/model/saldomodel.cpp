#include "model/saldomodel.h"

#include "model/databasestructure.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>

namespace membermanager
{
namespace model
{

SaldoModel::SaldoModel(const MemberFilter &aFilter, const QSqlDatabase &aDb, QObject *aParent) :
    model(new QSqlTableModel(aParent, aDb))
{
    model->setObjectName(SaldoTable::TABLENAME);
    model->setTable(SaldoTable::TABLENAME);
    model->setHeaderData(SaldoTable::betrag, Qt::Horizontal, aParent->tr("Betrag"));
    model->setHeaderData(SaldoTable::datum, Qt::Horizontal, aParent->tr("Valuta Datum"));
    model->setHeaderData(SaldoTable::bezeichnung, Qt::Horizontal, aParent->tr("Bezeichnung"));
    model->setHeaderData(SaldoTable::barkonto, Qt::Horizontal, aParent->tr("Barkonto"));
    model->setHeaderData(SaldoTable::konten, Qt::Horizontal, aParent->tr("Konten"));
    model->setHeaderData(SaldoTable::kasse_pkey, Qt::Horizontal, aParent->tr("Kassa Id"));
    model->setHeaderData(SaldoTable::info, Qt::Horizontal, aParent->tr("Info"));

    model->setFilter(aFilter.createFilter());
    model->select();
}

SaldoModel::~SaldoModel()
{
}

QString SaldoModel::getMemberId() const
{
    QSqlRecord record = model->record(0);
    QVariant id = record.value(SaldoTable::dorfmitglied_pkey);
    return id.toString();
}

double SaldoModel::amount() const
{
    /// \todo use MemberFilter and use SaldoTable::TABLENAME
    QString query = QString("SELECT SUM(betrag) FROM saldo WHERE dorfmitglied_pkey=%1").arg(getMemberId());
    QSqlQuery sqlQuery(query);
    sqlQuery.next();
    QVariant sum = sqlQuery.value(0);
    return sum.toFloat();
}

void SaldoModel::initTableView(QTableView *aTableView) const
{
    aTableView->setModel(model);
    aTableView->setColumnHidden(SaldoTable::saldo_pkey, true);
    aTableView->setColumnHidden(SaldoTable::dorfmitglied_pkey, true);

    aTableView->sortByColumn(SaldoTable::saldo_pkey, Qt::DescendingOrder);
}

QModelIndex SaldoModel::insertNewRow()
{
    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row, SaldoTable::dorfmitglied_pkey), getMemberId());
    model->submitAll();
    /// \todo model.lastError();
    return model->index(row, SaldoTable::betrag);
}

bool SaldoModel::deleteRow(const QModelIndex &anIndex)
{
    return model->removeRow(anIndex.row());
    /// \todo model.lastError();
}

}
}
