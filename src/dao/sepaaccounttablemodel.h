#ifndef MEMBERMANAGER_DAO_SEPAACCOUNTTABLEMODEL_H
#define MEMBERMANAGER_DAO_SEPAACCOUNTTABLEMODEL_H

#include <QVariant>

#include "entity/sepaaccount.h"

namespace membermanager {
namespace dao {

class SepaAccountTableModel
{
public:
    static entity::SepaAccount *findByMemberId(QVariant id);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_SEPAACCOUNTTABLEMODEL_H
