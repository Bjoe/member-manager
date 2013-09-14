#ifndef MEMBERMANAGER_ACCOUNTING_MEMBERADDITIONALSUM_H
#define MEMBERMANAGER_ACCOUNTING_MEMBERADDITIONALSUM_H

#include <QMap>

#include "accounting/arithmetic.h"
#include "entity/contribution.h"

namespace membermanager {
namespace accounting {

class MemberAdditionalSum : public Arithmetic
{
public:
    MemberAdditionalSum(const Arithmetic &arithmetic = Arithmetic());

    virtual void calculate(const entity::Contribution *contribution);

    QMap<double, double> getSumMap() const;
    double getFeeSum() const;
    double getDonationSum() const;

    void addToSumMap(double fee);
private:
    Arithmetic m_arithmetic;
    QMap<double, double> m_sumMap;
    double m_feeSum;
    double m_donationSum;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_MEMBERADDITIONALSUM_H
