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
    return model;
}

entity::CashAccount *CashAccountTableModel::findBySelectedRow(QSqlTableModel *model, int row)
{
    QSqlRecord record = model->record(row);
    QVariant id = record.value("cashAccountId");

    QDjangoQuerySet<entity::CashAccount> cashAccounts;
    QDjangoQuerySet<entity::CashAccount> result = cashAccounts.filter(QDjangoWhere("cashAccountId", QDjangoWhere::Equals, id));

    entity::CashAccount *cashAccount = new entity::CashAccount();
    result.at(0, cashAccount);
    return cashAccount;
}

} // namespace dao
} // namespace membermanager
