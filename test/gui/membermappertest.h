#ifndef MEMBERMAPPERTEST_H
#define MEMBERMAPPERTEST_H

#include <QtTest/QtTest>

namespace membermanagertest
{
namespace gui
{

class MemberMapperTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void showMember();
    void changeMember();
};

}
}

#endif // MEMBERMAPPERTEST_H
