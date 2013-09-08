#include "bankaccounttablemodel.h"

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

entity::BankAccount *BankAccountTableModel::findByMemberId(QVariant id)
{
    QDjangoQuerySet<entity::BankAccount> querySet;
    QDjangoQuerySet<entity::BankAccount> result = querySet.filter(QDjangoWhere("memberId", QDjangoWhere::Equals, id));

    entity::BankAccount *bankAccount = new entity::BankAccount();
    result.at(0, bankAccount);
    return bankAccount;
}


} // namespace dao
} // namespace membermanager
