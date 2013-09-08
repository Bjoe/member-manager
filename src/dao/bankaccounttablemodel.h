#ifndef MEMBERMANAGER_DAO_BANKACCOUNTTABLEMODEL_H
#define MEMBERMANAGER_DAO_BANKACCOUNTTABLEMODEL_H

#include <QVariant>

#include "entity/bankaccount.h"

namespace membermanager {
namespace dao {

class BankAccountTableModel
{
public:
    static entity::BankAccount *findByMemberId(QVariant id);
};

} // namespace dao
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_BANKACCOUNTTABLEMODEL_H
