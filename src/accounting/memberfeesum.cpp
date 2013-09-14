#include "memberfeesum.h"

namespace membermanager {
namespace accounting {

MemberFeeSum::MemberFeeSum(const Arithmetic &arithmetic)
    : m_arithmetic(arithmetic), m_sumMap(), m_sum(0)
{

}

void MemberFeeSum::calculate(const entity::Contribution *contribution)
{
    double fee = contribution->fee();
    if(fee > 0) {
        m_sum += fee;

        double sum = fee;
        if(m_sumMap.contains(fee)) {
            sum += m_sumMap.value(fee);
        }
        m_sumMap.insert(fee, sum);
    }

    m_arithmetic.calculate(contribution);
}

double MemberFeeSum::getSum() const
{
    return m_sum;
}

QMap<double, double> MemberFeeSum::getSumMap() const
{
    return m_sumMap;
}

} // namespace accounting
} // namespace membermanager
