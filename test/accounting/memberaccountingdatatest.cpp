
#include <QtTest/QtTest>

#include <QString>

#include "entity/member.h"

#include "accounting/memberaccountingdata.h"

namespace test {
namespace accounting {

class MemberAccountingDataTest : public QObject
{
    Q_OBJECT

private slots:
    void testCanCharge();
    void testDontCanCharge();
};

void MemberAccountingDataTest::testCanCharge()
{
    membermanager::accounting::MemberAccountingData data;
    data.setBankAccountNumber("123456");
    data.setBankCode("123456");
    data.setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));

    QVERIFY(data.canCharge());
}

void MemberAccountingDataTest::testDontCanCharge()
{
    membermanager::accounting::MemberAccountingData data;

    QVERIFY(data.canCharge() == false);

    data.setCollectionState(static_cast<char>(membermanager::entity::Member::CollectionState::known));

    QVERIFY(data.canCharge() == true);
}

}
}

QTEST_MAIN(test::accounting::MemberAccountingDataTest)
#include "moc_memberaccountingdatatest.cpp"


