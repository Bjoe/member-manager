
#include <QtTest/QtTest>

#include "testconfig.h"

#include "entity/contribution.h"

#include "accounting/memberdonationsum.h"

namespace test {
namespace accounting {

class MemberDonationSumTest : public QObject
{
    Q_OBJECT

private slots:
    void testCalculate();
};

void MemberDonationSumTest::testCalculate()
{
    membermanager::entity::Contribution contribution1;
    contribution1.setDonation(0);

    membermanager::entity::Contribution contribution2;
    contribution2.setDonation(10);

    membermanager::entity::Contribution contribution3;

    membermanager::accounting::MemberDonationSum sumDonation;

    sumDonation.calculate(&contribution2);

    QCOMPARE(sumDonation.getCount(), 1);
    double sum = 10;
    QCOMPARE(sumDonation.getSum(), sum);


    sumDonation.calculate(&contribution1);
    sumDonation.calculate(&contribution3);

    QCOMPARE(sumDonation.getCount(), 1);
    QCOMPARE(sumDonation.getSum(), sum);


    sumDonation.calculate(&contribution2);

    QCOMPARE(sumDonation.getCount(), 2);
    sum = 20;
    QCOMPARE(sumDonation.getSum(), sum);
}

}
}

QTEST_MAIN(test::accounting::MemberDonationSumTest)
#include "moc_memberdonationsumtest.cpp"
