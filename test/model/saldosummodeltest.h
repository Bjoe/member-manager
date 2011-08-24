#ifndef SALDOSUMMODELTEST_H
#define SALDOSUMMODELTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Model
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

#endif	/* // SALDOSUMMODELTEST_H */
