#ifndef SUMMARYWINDOWTEST_H
#define SUMMARYWINDOWTEST_H

#include <QtTest/QtTest>

namespace membermanagertest
{
namespace gui
{

class SummaryWindowTest : public QObject
{
    Q_OBJECT

public:
    SummaryWindowTest();

public slots:
    void buttonClicked();

private:
    bool isClicked;

private slots:
    void testShowSummary();
    void testAddButton();
};

}
}

#endif // SUMMARYWINDOWTEST_H
