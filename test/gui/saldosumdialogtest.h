#ifndef SALDOSUMDIALOGTEST_H
#define SALDOSUMDIALOGTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Gui
{

class SaldoSumDialogTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
};

}
}

#endif  /* // SALDOSUMDIALOGTEST_H */
