#ifndef COUNTMEMBERSUMMARYTEST_H
#define COUNTMEMBERSUMMARYTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class CountMemberSummaryTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCountMember();
};

}

#endif // COUNTMEMBERSUMMARYTEST_H
