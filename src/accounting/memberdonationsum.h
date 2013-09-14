#ifndef MEMBERMANAGER_ACCOUNTING_MEMBERDONATIONSUM_H
#define MEMBERMANAGER_ACCOUNTING_MEMBERDONATIONSUM_H

#include "entity/contribution.h"
#include "accounting/arithmetic.h"

namespace membermanager {
namespace accounting {

class MemberDonationSum : public Arithmetic
{
public:
    MemberDonationSum(const Arithmetic &arithmetic = Arithmetic());

    virtual void calculate(const entity::Contribution *contribution);

    double getSum() const;
    int getCount() const;

private:
    Arithmetic m_arithmetic;
    double m_sum;
    int m_count;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_MEMBERDONATIONSUM_H
