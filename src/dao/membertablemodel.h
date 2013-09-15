#ifndef MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H
#define MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H

#include <QVariant>
#include <QList>
#include <QSqlTableModel>

#include "entity/member.h"

namespace membermanager {
namespace dao {

class MemberTableModel
{
public:
    static QSqlTableModel *createModel(entity::Member::State state);
    static QVariant giveMemberIdByRow(QSqlTableModel *model, int row);
    static entity::Member *findByMemberId(QVariant id);
    static void selectState(QSqlTableModel *model, entity::Member::State state);
    static QList<entity::Member *> findByState(entity::Member::State state);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H
