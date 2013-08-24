#ifndef MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H
#define MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H

#include <QSqlTableModel>

namespace membermanager {
namespace dao {

class MemberTableModel
{
public:
    static QSqlTableModel *createModel();
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_MEMBERTABLEMODELFACTORY_H
