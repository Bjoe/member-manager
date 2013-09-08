#include "contributiontablemodel.h"

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

QSqlTableModel *ContributionTableModel::createModel(QVariant memberId)
{
    QString whereClause = QString("%1 = %2").arg("memberId").arg(memberId.toString());
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("Contribution");
    model->setFilter(whereClause);
    model->select();

    return model;
}

entity::Contribution *ContributionTableModel::findByMemberId(QVariant id)
{
    QDjangoQuerySet<entity::Contribution> querySet;
    QDjangoQuerySet<entity::Contribution> result = querySet.filter(QDjangoWhere("memberId", QDjangoWhere::Equals, id));

    entity::Contribution *contribution = new entity::Contribution();
    result.at(0, contribution);
    return contribution;
}

} // namespace dao
} // namespace membermanager
