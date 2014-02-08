#ifndef MEMBERMANAGER_DAO_BALANCETABLEMODEL_H
#define MEMBERMANAGER_DAO_BALANCETABLEMODEL_H

#include <QObject>
#include <QDate>
#include <QList>
#include <QVariant>
#include <QSqlTableModel>

#include "entity/balance.h"

namespace membermanager {
namespace dao {

class BalanceTableModel
{
public:
    static QSqlTableModel* createModel(const QVariant& memberId);
    static entity::Balance* giveBalanceByRow(const QSqlTableModel* model, int row);
    static QList<QObject* > findContributionByMemberIdAndYear(const QVariant& memberId, const QVariant& year);
    static double calculateFeeSumByMemberId(const QVariant& memberId, const QDate &valuta);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_BALANCETABLEMODEL_H
