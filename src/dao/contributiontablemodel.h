#ifndef MEMBERMANAGER_DAO_CONTRIBUTIONTABLEMODEL_H
#define MEMBERMANAGER_DAO_CONTRIBUTIONTABLEMODEL_H

#include <QVariant>
#include "entity/contribution.h"

namespace membermanager {
namespace dao {

class ContributionTableModel
{
public:
    static entity::Contribution *findByMemberId(QVariant id);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CONTRIBUTIONTABLEMODEL_H
