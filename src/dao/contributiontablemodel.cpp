#include "contributiontablemodel.h"

#include <QStringList>

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

QSqlTableModel* ContributionTableModel::createModel(QVariant memberId)
{
    QString whereClause = QString("%1 = %2").arg("memberId").arg(memberId.toString());
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("Contribution");
    model->setFilter(whereClause);
    model->setSort(7, Qt::DescendingOrder);
    model->select();

    return model;
}

entity::Contribution* ContributionTableModel::findLastEntryByMemberId(QVariant id)
{
    QDjangoQuerySet<entity::Contribution> result = QDjangoQuerySet<entity::Contribution>()
            .filter(QDjangoWhere("memberId", QDjangoWhere::Equals, id))
            .orderBy(QStringList() << "-validFrom");

    return result.at(0);
}

entity::Contribution* ContributionTableModel::findByMemberIdWithPointInTime(QVariant id, QDate pointInTime)
{
    QDjangoQuerySet<entity::Contribution> result = QDjangoQuerySet<entity::Contribution>()
            .filter(QDjangoWhere("memberId", QDjangoWhere::Equals, id))
            .orderBy(QStringList() << "-validFrom");

    entity::Contribution* last;
    for(int i = 0; i < result.size(); ++i) {
        entity::Contribution* contribution = result.at(i);
        QDate validFrom = contribution->validFrom();
        if(validFrom < pointInTime) { // TODO in SQL
            last = contribution;
            break;
        } else {
            delete contribution;
        }
    }
    return last;
}

} // namespace dao
} // namespace membermanager
