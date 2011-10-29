#ifndef SALDOSUMMODELTEST_H
#define SALDOSUMMODELTEST_H

#include <QtTest/QtTest>

namespace membermanagertest
{
namespace model
{

class SaldoSumModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testView();
};

}
}

#endif  /* // SALDOSUMMODELTEST_H */
