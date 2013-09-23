#ifndef MEMBERMANAGER_ACCOUNTING_MEMBERACCOUNTINGDATA_H
#define MEMBERMANAGER_ACCOUNTING_MEMBERACCOUNTINGDATA_H

#include <QString>
#include <QVariant>
#include <QDate>

#include "entity/member.h"

namespace membermanager {
namespace accounting {

class MemberAccountingData
{
public:
    MemberAccountingData(const entity::Member* member, const QDate &date = QDate::currentDate());

    QDate date() const;
    QVariant memberId() const;
    QString name() const;
    QString firstname() const;
    QString bankAccountNumber() const;
    QString bankCode() const;
    double fee() const;
    double donation() const;
    double additionalFee() const;
    double additionalDonation() const;
    double amortization() const;

private:
    QDate m_date;
    QVariant m_memberId;
    QString m_name;
    QString m_firstname;
    QString m_bankAccountNumber;
    QString m_bankCode;
    double m_fee;
    double m_donation;
    double m_additionalFee;
    double m_additionalDonation;
    double m_amortization;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_MEMBERACCOUNTINGDATA_H
