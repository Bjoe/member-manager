#ifndef MEMBERFILTERTEST_H_
#define MEMBERFILTERTEST_H_

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Model
{

class MemberFilterTest: public QObject
{
    Q_OBJECT

private slots:
    void testSetDeleted();
    void testSetDeletedFalse();
};

}
}

#endif /* MEMBERFILTERTEST_H_ */