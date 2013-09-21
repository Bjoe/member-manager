#ifndef MEMBERMANAGER_DAO_CONTRIBUTIONTABLEMODEL_H
#define MEMBERMANAGER_DAO_CONTRIBUTIONTABLEMODEL_H

#include <QDate>
#include <QVariant>
#include <QSqlTableModel>

#include "entity/contribution.h"

namespace membermanager {
namespace dao {

class ContributionTableModel
{
public:
    static QSqlTableModel* createModel(QVariant memberId);
    static entity::Contribution* findLastEntryByMemberId(QVariant id);
    static entity::Contribution* findByMemberIdWithPointInTime(QVariant id, QDate pointInTime);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CONTRIBUTIONTABLEMODEL_H
