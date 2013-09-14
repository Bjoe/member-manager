#include "memberdonationsum.h"

namespace membermanager {
namespace accounting {

MemberDonationSum::MemberDonationSum(const Arithmetic &arithmetic)
    : m_arithmetic(arithmetic), m_sum(0), m_count(0)
{
}

void MemberDonationSum::calculate(const entity::Contribution *contribution)
{
    double donation = contribution->donation();
    if(donation > 0) {
        ++m_count;
        m_sum += donation;
    }

    m_arithmetic.calculate(contribution);
}

double MemberDonationSum::getSum() const
{
    return m_sum;
}

int MemberDonationSum::getCount() const
{
    return m_count;
}

} // namespace accounting
} // namespace membermanager
