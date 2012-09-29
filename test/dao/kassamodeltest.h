#ifndef KASSAMODELTEST_H_
#define KASSAMODELTEST_H_

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace dao
{
/// \todo rename Kassa in Cash
class KassaModelTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testModel();
};

}
}

#endif /* KASSAMODELTEST_H_ */