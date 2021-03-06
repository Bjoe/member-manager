#include "contributionentrytest.h"

#include "accounting/contributionentry.h"

#include <QDate>

namespace membermanagertest {
namespace accounting {

void ContributionEntryTest::testCreateEntry()
{
    QDate date = QDate::currentDate();

    membermanager::accounting::ContributionEntry entry(1);
    entry.setDonation(5.50);
    entry.setFee(15);
    entry.setAdditionalFee(5);
    entry.setInfo("foo");
    entry.setValidFrom(date);

    QCOMPARE(entry.getMemberId(), 1);
    double donation = 5.50;
    QCOMPARE(entry.getDonation(), donation);
    double fee = 15.00;
    QCOMPARE(entry.getFee(), fee);
    double additionalFee = 5.00;
    QCOMPARE(entry.getAdditionalFee(), additionalFee);
    QCOMPARE(entry.getValidFrom(), date);
}


} // namespace accounting
} // namespace membermanagertest

QTEST_MAIN(membermanagertest::accounting::ContributionEntryTest)
#include "moc_contributionentrytest.cpp"
