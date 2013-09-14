
#include <QtTest/QtTest>

#include <QMap>

#include "testconfig.h"

#include "entity/contribution.h"

#include "accounting/memberadditionalsum.h"

namespace test {
namespace accounting {

class MemberAdditionalSumTest : public QObject
{
    Q_OBJECT

private slots:
    void testCalculate();
};

void MemberAdditionalSumTest::testCalculate()
{
    membermanager::entity::Contribution contribution1;
    contribution1.setAdditionalFee(0);
    contribution1.setAdditionalDonation(0);

    membermanager::entity::Contribution contribution2;
    contribution2.setAdditionalFee(3.5);
    contribution2.setAdditionalDonation(1.5);

    membermanager::entity::Contribution contribution3;

    membermanager::accounting::MemberAdditionalSum memberSum;

    memberSum.calculate(&contribution2);

    double fee = 3.5;
    double donation = 1.5;

    QMap<double, double> sumMap = memberSum.getSumMap();
    QCOMPARE(sumMap.value(fee), fee);
    QCOMPARE(sumMap.value(donation), donation);
    QCOMPARE(memberSum.getFeeSum(), fee);
    QCOMPARE(memberSum.getDonationSum(), donation);

    memberSum.calculate(&contribution1);
    memberSum.calculate(&contribution3);

    sumMap = memberSum.getSumMap();
    QCOMPARE(sumMap.value(fee), fee);
    QCOMPARE(sumMap.value(donation), donation);
    QCOMPARE(memberSum.getFeeSum(), fee);
    QCOMPARE(memberSum.getDonationSum(), donation);

    memberSum.calculate(&contribution2);
    sumMap = memberSum.getSumMap();
    fee = 7;
    donation = 3;
    QCOMPARE(sumMap.value(3.5), fee);
    QCOMPARE(sumMap.value(1.5), donation);
    QCOMPARE(memberSum.getFeeSum(), fee);
    QCOMPARE(memberSum.getDonationSum(), donation);
}

}
}

QTEST_MAIN(test::accounting::MemberAdditionalSumTest)
#include "moc_memberadditionalsumtest.cpp"
