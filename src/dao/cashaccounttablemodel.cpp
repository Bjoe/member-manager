#include "cashaccounttablemodel.h"

#include <QVariant>
#include <QSqlRecord>

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

QSqlTableModel* CashAccountTableModel::createModel(int year)
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("CashAccount");
    selectYear(model, year);
    return model;
}

void CashAccountTableModel::selectYear(QSqlTableModel *model, int year)
{
    QString whereClause = QString("valuta BETWEEN '%1-01-01' AND '%1-12-31'").arg(year);
    model->setFilter(whereClause);
    model->select();

    while(model->canFetchMore())
        model->fetchMore();
}

entity::CashAccount* CashAccountTableModel::findBySelectedRow(const QSqlTableModel* model, int row)
{
    QSqlRecord record = model->record(row);
    QVariant id = record.value("cashAccountId");

    return QDjangoQuerySet<entity::CashAccount>()
            .get(QDjangoWhere("cashAccountId", QDjangoWhere::Equals, id));
}

} // namespace dao
} // namespace membermanager
