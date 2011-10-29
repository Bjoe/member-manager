#ifndef MEMBERFILTERTEST_H_
#define MEMBERFILTERTEST_H_

#include <QtTest/QtTest>

namespace membermanagertest
{
namespace model
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
