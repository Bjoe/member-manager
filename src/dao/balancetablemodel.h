#ifndef MEMBERMANAGER_DAO_BALANCETABLEMODEL_H
#define MEMBERMANAGER_DAO_BALANCETABLEMODEL_H

#include <QObject>
#include <QVariant>
#include <QList>
#include <QSqlTableModel>

#include "entity/balance.h"

namespace membermanager {
namespace dao {

class BalanceTableModel
{
public:
    static QSqlTableModel *createModel(QVariant memberId);
    static entity::Balance* giveBalanceByRow(const QSqlTableModel* model, int row);
    static QList<QObject *> findContributionByMemberIdAndYear(QVariant memberId, QVariant year);
    static double calculateFeeSumByMemberId(QVariant memberId);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_BALANCETABLEMODEL_H
