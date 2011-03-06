#ifndef MEMBERTEST_H
#define MEMBERTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class MemberTest : public QObject
{
    Q_OBJECT

private slots:
    void testDefaultKonstruktor();
    void testMember();
};

}

#endif // MEMBERTEST_H

