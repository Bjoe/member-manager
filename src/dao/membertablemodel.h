#ifndef MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H
#define MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H

#include <QSqlTableModel>

#include "entity/member.h"

namespace membermanager {
namespace dao {

class MemberTableModel
{
public:
    static QSqlTableModel *createModel(entity::Member::State state);
    static entity::Member *findMemberByRow(QSqlTableModel *model, int row);
    static void selectState(QSqlTableModel *model, entity::Member::State state);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H
