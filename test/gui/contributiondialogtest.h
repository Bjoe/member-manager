#ifndef CONTRIBUTIONDIALOGTEST_H
#define CONTRIBUTIONDIALOGTEST_H

#include <QtTest/QtTest>

namespace membermanagertest
{
namespace gui
{

class ContributionDialogTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testShowDialog();
};

}
}

#endif // CONTRIBUTIONDIALOGTEST_H
