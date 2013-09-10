#include "balancetablemodel.h"

#include <QString>

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

QSqlTableModel *BalanceTableModel::createModel(QVariant memberId)
{
    QString whereClause = QString("%1 = %2").arg("memberId").arg(memberId.toString());

    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("Balance");
    model->setFilter(whereClause);
    model->select();

    return model;
}

QList<entity::Balance *> BalanceTableModel::findContributionByMemberIdAndYear(QVariant memberId, QVariant year)
{
    QDjangoQuerySet<entity::Balance> querySet;
    QDjangoQuerySet<entity::Balance> result = querySet.filter(QDjangoWhere("memberId", QDjangoWhere::Equals, memberId) &&
                                                              (QDjangoWhere("account", QDjangoWhere::Equals, "11") ||
                                                               QDjangoWhere("account", QDjangoWhere::Equals, "12")));

    QList<entity::Balance *> list;

    for(int i = 0; i < result.size(); ++i) {
        entity::Balance *balance = new entity::Balance();
        result.at(i, balance);
        if(balance->valuta().year() == year) // TODO In SQL
            list.append(balance);
    }

    return list;
}

} // namespace dao
} // namespace membermanager
