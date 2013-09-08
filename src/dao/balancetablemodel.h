#ifndef MEMBERMANAGER_DAO_BALANCETABLEMODEL_H
#define MEMBERMANAGER_DAO_BALANCETABLEMODEL_H

#include <QVariant>
#include <QSqlTableModel>

namespace membermanager {
namespace dao {

class BalanceTableModel
{
public:
    static QSqlTableModel *createModel(QVariant memberId);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_BALANCETABLEMODEL_H
