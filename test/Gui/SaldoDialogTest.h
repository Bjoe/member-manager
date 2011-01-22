#ifndef SALDODIALOGTEST_H
#define SALDODIALOGTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class SaldoDialogTest : public QObject
{
Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
    void testShowSum();
};

}

#endif // SALDODIALOGTEST_H
