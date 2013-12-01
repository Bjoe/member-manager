#include "sepaaccounttablemodel.h"

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

entity::SepaAccount *SepaAccountTableModel::findByMemberId(QVariant id)
{
    QDjangoQuerySet<entity::SepaAccount> result = QDjangoQuerySet<entity::SepaAccount>().
            filter(QDjangoWhere("memberId", QDjangoWhere::Equals, id));

    entity::SepaAccount* sepaAccount = new entity::SepaAccount();
    if(result.size() > 0) {
        result.at(0, sepaAccount);
    }
    return sepaAccount;
}

} // namespace dao
} // namespace membermanager
