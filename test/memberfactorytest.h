#ifndef MEMBERFACTORYTEST_H
#define MEMBERFACTORYTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class MemberFactoryTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testCreateNewMember();
    void testCreateExistsMember();
};

}

#endif // MEMBERFACTORYTEST_H