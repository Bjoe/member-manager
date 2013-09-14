
#include <QtTest/QtTest>

#include <QMap>

#include "testconfig.h"

#include "entity/contribution.h"

#include "accounting/memberfeesum.h"

namespace test {
namespace accounting {

class MemberFeeSumTest : public QObject
{
    Q_OBJECT

private slots:
    void testCalculate();
};

void MemberFeeSumTest::testCalculate()
{
    membermanager::entity::Contribution contribution1;
    contribution1.setFee(0);

    membermanager::entity::Contribution contribution2;
    contribution2.setFee(15.0);

    membermanager::entity::Contribution contribution3;

    membermanager::accounting::MemberFeeSum feeSum;

    feeSum.calculate(&contribution2);

    double sum = 15.0;
    QCOMPARE(feeSum.getSum(), sum);
    QMap<double, double> sumMap = feeSum.getSumMap();
    QCOMPARE(sumMap.value(sum), sum);

    feeSum.calculate(&contribution1);
    feeSum.calculate(&contribution3);

    QCOMPARE(feeSum.getSum(), sum);
    sumMap = feeSum.getSumMap();
    QCOMPARE(sumMap.value(sum), sum);

    feeSum.calculate(&contribution2);

    sum = 30.0;
    QCOMPARE(feeSum.getSum(), sum);
    sumMap = feeSum.getSumMap();
    QCOMPARE(sumMap.value(15.0), sum);
}

}
}


QTEST_MAIN(test::accounting::MemberFeeSumTest)
#include "moc_memberfeesumtest.cpp"
