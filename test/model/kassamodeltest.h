#ifndef KASSAMODELTEST_H_
#define KASSAMODELTEST_H_

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Model
{

class KassaModelTest: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testModel();
};

}
}

#endif /* KASSAMODELTEST_H_ */
