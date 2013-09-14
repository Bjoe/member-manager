#ifndef MEMBERMANAGER_ACCOUNTING_MEMBERFEESUM_H
#define MEMBERMANAGER_ACCOUNTING_MEMBERFEESUM_H

#include <QMap>

#include "entity/contribution.h"
#include "accounting/arithmetic.h"

namespace membermanager {
namespace accounting {

class MemberFeeSum : public Arithmetic
{
public:
    MemberFeeSum(const Arithmetic &arithmetic = Arithmetic());

    void calculate(const entity::Contribution *contribution);

    double getSum() const;

    QMap<double, double> getSumMap() const;

private:
    Arithmetic m_arithmetic;
    QMap<double, double> m_sumMap;
    double m_sum;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_MEMBERFEESUM_H
