#ifndef MEMBERDAOTEST_H
#define MEMBERDAOTEST_H

#include <QtTest/QtTest>

namespace membermanagertest
{
namespace model
{

class MemberDaoTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testNewMember();
    void testDeleteMember();
};

}
}

#endif // MEMBERDAOTEST_H
