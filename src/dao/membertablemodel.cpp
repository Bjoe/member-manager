#include "membertablemodel.h"

namespace membermanager {
namespace dao {

QSqlTableModel *MemberTableModel::createModel()
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("member");
    model->select();
    return model;
}


} // namespace dao
} // namespace membermanager
