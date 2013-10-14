#include "cashaccounttablemodel.h"

#include <QVariant>
#include <QSqlRecord>

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

QSqlTableModel *CashAccountTableModel::createModel()
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("CashAccount");
    model->select();

    while(model->canFetchMore())
        model->fetchMore();

    return model;
}

entity::CashAccount *CashAccountTableModel::findBySelectedRow(QSqlTableModel *model, int row)
{
    QSqlRecord record = model->record(row);
    QVariant id = record.value("cashAccountId");

    return QDjangoQuerySet<entity::CashAccount>()
            .get(QDjangoWhere("cashAccountId", QDjangoWhere::Equals, id));
}

} // namespace dao
} // namespace membermanager
