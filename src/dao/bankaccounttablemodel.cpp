#include "bankaccounttablemodel.h"

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

entity::BankAccount *BankAccountTableModel::findByMemberId(QVariant id)
{
    QDjangoQuerySet<entity::BankAccount> result = QDjangoQuerySet<entity::BankAccount>().
            filter(QDjangoWhere("memberId", QDjangoWhere::Equals, id));

    entity::BankAccount* bankAccount = new entity::BankAccount();
    if(result.size() > 0) {
        result.at(0, bankAccount);
    }
    return bankAccount;
}


} // namespace dao
} // namespace membermanager
