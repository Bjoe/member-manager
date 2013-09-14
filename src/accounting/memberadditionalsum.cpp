#include "memberadditionalsum.h"

namespace membermanager {
namespace accounting {

MemberAdditionalSum::MemberAdditionalSum(const Arithmetic &arithmetic)
    : m_arithmetic(arithmetic), m_sumMap(), m_feeSum(0), m_donationSum(0)
{

}

void MemberAdditionalSum::addToSumMap(double fee)
{
    double sum = fee;
    if(m_sumMap.contains(fee)) {
        sum += m_sumMap.value(fee);
    }
    m_sumMap.insert(fee, sum);
}

void MemberAdditionalSum::calculate(const entity::Contribution *contribution)
{
    double fee = contribution->additionalFee();
    if(fee > 0) {
        m_feeSum += fee;
        addToSumMap(fee);
    }

    double donation = contribution->additionalDonation();
    if(donation > 0) {
        m_donationSum += donation;
        addToSumMap(donation);
    }

    m_arithmetic.calculate(contribution);
}

QMap<double, double> MemberAdditionalSum::getSumMap() const
{
    return m_sumMap;
}

double MemberAdditionalSum::getFeeSum() const
{
    return m_feeSum;
}

double MemberAdditionalSum::getDonationSum() const
{
    return m_donationSum;
}

} // namespace accounting
} // namespace membermanager
