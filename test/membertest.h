#ifndef MEMBERTEST_H
#define MEMBERTEST_H

#include <QtTest/QtTest>

namespace membermanagertest
{

class MemberTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testMember();
};

}

#endif // MEMBERTEST_H

