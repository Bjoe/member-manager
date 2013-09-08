#include "contributiontablemodel.h"

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

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
