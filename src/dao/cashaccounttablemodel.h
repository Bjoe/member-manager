#ifndef MEMBERMANAGER_DAO_CASHACCOUNTTABLEMODEL_H
#define MEMBERMANAGER_DAO_CASHACCOUNTTABLEMODEL_H

#include <QSqlTableModel>

#include "entity/cashaccount.h"

namespace membermanager {
namespace dao {

class CashAccountTableModel
{
public:
    static QSqlTableModel *createModel();
    static entity::CashAccount *findBySelectedRow(QSqlTableModel *model, int row);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CASHACCOUNTTABLEMODEL_H
