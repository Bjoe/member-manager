#ifndef SALDOSUMMODELTEST_H
#define SALDOSUMMODELTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{
/// \todo rename Saldo in Balance
class SaldoSumModelTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testView();
};

}
}

#endif  /* // SALDOSUMMODELTEST_H */
