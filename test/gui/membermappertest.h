#ifndef MEMBERMAPPERTEST_H
#define MEMBERMAPPERTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Gui
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
