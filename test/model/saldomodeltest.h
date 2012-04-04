#ifndef SALDOMODELTEST_H_
#define SALDOMODELTEST_H_

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{
/// \todo rename Salod in Balance
class SaldoModelTest: public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testModel();
    void testAmount();
    void testGetMemberId();
    void testInsertAndDeleteRow();
};

}
}

#endif /* SALDOMODELTEST_H_ */
