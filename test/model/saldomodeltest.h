#ifndef SALDOMODELTEST_H_
#define SALDOMODELTEST_H_

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{

class SaldoModelTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testModel();
    void testAmount();
};

}
}

#endif /* SALDOMODELTEST_H_ */
