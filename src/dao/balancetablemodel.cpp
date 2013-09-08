#include "balancetablemodel.h"

#include <QString>

namespace membermanager {
namespace dao {

QSqlTableModel *BalanceTableModel::createModel(QVariant memberId)
{
    QString whereClause = QString("%1 = %2").arg("memberId").arg(memberId.toString());

    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("Balance");
    model->setFilter(whereClause);
    model->select();

    return model;
}

} // namespace dao
} // namespace membermanager
