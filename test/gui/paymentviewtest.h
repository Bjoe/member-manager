#ifndef MEMBERMANAGERTEST_GUI_PAYMENTVIEWTEST_H
#define MEMBERMANAGERTEST_GUI_PAYMENTVIEWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class PaymentViewTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testCalculate();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_PAYMENTVIEWTEST_H
