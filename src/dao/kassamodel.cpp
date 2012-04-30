#include "dao/kassamodel.h"

#include "dao/databasestructure.h"

namespace membermanager
{
namespace dao
{

KassaModel::KassaModel(const QSqlDatabase &aDb) :
    model(new QSqlTableModel(this, aDb))
{
    model->setTable(KassaTable::TABLENAME);
    model->setObjectName(KassaTable::TABLENAME);
    setDefaultFilter();
    refresh();
}

KassaModel::~KassaModel()
{
    delete model;
}

void KassaModel::setDefaultFilter()
{
    model->setFilter(KassaTable::COLUMNNAME[KassaTable::deleted] + "='false'");
}

void KassaModel::refresh()
{
    model->select();
}

void KassaModel::initTableView(QTableView *aTableView) const
{
    aTableView->setModel(model);
    aTableView->setColumnHidden(KassaTable::kasse_pkey, true);
    aTableView->setColumnHidden(KassaTable::deleted, true);

    aTableView->sortByColumn(KassaTable::kasse_pkey, Qt::DescendingOrder);
}

}
}
