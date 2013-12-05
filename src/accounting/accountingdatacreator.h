#ifndef MEMBERMANAGER_ACCOUNTING_ACCOUNTINGDATACREATOR_H
#define MEMBERMANAGER_ACCOUNTING_ACCOUNTINGDATACREATOR_H

#include <QString>
#include <QDate>

#include "entity/member.h"

#include "accounting/memberaccountingdata.h"

namespace membermanager {
namespace accounting {

class AccountingDataCreator
{
public:
    AccountingDataCreator(QDate valuta, QString purpose, QString accountingInfo, int accountingRefernce);

    MemberAccountingData* create(const entity::Member *member);

    int getAccountingReference() const;

private:
    QDate m_valuta;
    QString m_purpose;
    QString m_accountingInfo;
    int m_accountingReference;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_ACCOUNTINGDATACREATOR_H
