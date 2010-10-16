#ifndef SALDODIALOGTEST_H
#define SALDODIALOGTEST_H

#include <QObject>
#include <QtTest/QtTest>

namespace ClubFrontendTest
{

class SaldoDialogTest : public QObject
{
Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
};

}

#endif // SALDODIALOGTEST_H
