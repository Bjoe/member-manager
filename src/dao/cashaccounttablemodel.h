#ifndef MEMBERMANAGER_DAO_CASHACCOUNTTABLEMODEL_H
#define MEMBERMANAGER_DAO_CASHACCOUNTTABLEMODEL_H

#include <QString>
#include <QSqlTableModel>

#include "entity/cashaccount.h"

namespace membermanager {
namespace dao {

class CashAccountTableModel
{
public:
    static QSqlTableModel* createModel(int year);
    static void selectYear(QSqlTableModel *model, int year);
    static entity::CashAccount* findBySelectedRow(const QSqlTableModel* model, int row);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CASHACCOUNTTABLEMODEL_H
