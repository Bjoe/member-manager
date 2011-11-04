#include "model/saldomodel.h"

#include "model/databasestructure.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QString>
#include <QVariant>

namespace membermanager
{
namespace model
{

SaldoModel::SaldoModel(int anId, const QSqlDatabase &aDb) :
    model(new QSqlTableModel(this))
{
    model->setObjectName(SaldoTable::TABLENAME);
    model->setTable(SaldoTable::TABLENAME);
    model->setHeaderData(SaldoTable::betrag, Qt::Horizontal, tr("Betrag"));
    model->setHeaderData(SaldoTable::datum, Qt::Horizontal, tr("Valuta Datum"));
    model->setHeaderData(SaldoTable::bezeichnung, Qt::Horizontal, tr("Bezeichnung"));
    model->setHeaderData(SaldoTable::barkonto, Qt::Horizontal, tr("Barkonto"));
    model->setHeaderData(SaldoTable::konten, Qt::Horizontal, tr("Konten"));
    model->setHeaderData(SaldoTable::kasse_pkey, Qt::Horizontal, tr("Kassa Id"));
    model->setHeaderData(SaldoTable::info, Qt::Horizontal, tr("Info"));

    QString columnname = SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey];
    QString filter = QString(columnname + " = %1").arg(anId);
    model->setFilter(filter);
    model->select();
}

SaldoModel::~SaldoModel()
{
}

double SaldoModel::amount() const
{
    QSqlRecord record = model->record(0);
    QVariant id = record.value(SaldoTable::dorfmitglied_pkey);
    QString query = QString("SELECT SUM(betrag) FROM saldo WHERE dorfmitglied_pkey=%1").arg(id.toString());
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

}
}
