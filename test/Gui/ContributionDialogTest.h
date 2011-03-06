#ifndef CONTRIBUTIONDIALOGTEST_H
#define CONTRIBUTIONDIALOGTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Gui
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
