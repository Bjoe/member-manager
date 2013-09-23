#include "bankaccounttablemodel.h"

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

entity::BankAccount *BankAccountTableModel::findByMemberId(QVariant id)
{
    return QDjangoQuerySet<entity::BankAccount>().
            get(QDjangoWhere("memberId", QDjangoWhere::Equals, id));
}


} // namespace dao
} // namespace membermanager
