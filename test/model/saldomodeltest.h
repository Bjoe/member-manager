#ifndef SALDOMODELTEST_H_
#define SALDOMODELTEST_H_

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Model
{

class SaldoModelTest: public QObject
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
