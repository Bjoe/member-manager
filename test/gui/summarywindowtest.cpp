#include "summarywindowtest.h"

#include "gui/summarywindow.h"

#include <QtCore/QtCore>
#include <QtGui>

namespace membermanagertest
{
namespace gui
{

SummaryWindowTest::SummaryWindowTest() : isClicked(false)
{}


void SummaryWindowTest::testShowSummary()
{
    membermanager::gui::SummaryWindow summary;

    summary.showSummary("foo");

    const QTextEdit *textEdit = summary.findChild<QTextEdit *> ("textEdit");

    QCOMPARE(textEdit->toPlainText(), QString("foo"));
}

void SummaryWindowTest::testAddButton()
{
    isClicked = false;
    membermanager::gui::SummaryWindow summary;

    QPushButton *button = new QPushButton();
    button->setObjectName("testButton");
    button->connect(button, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
    summary.addButton(button);

    QPushButton *testButton = summary.findChild<QPushButton *> ("testButton");
    QTest::mouseClick(testButton, Qt::LeftButton);

    QVERIFY(isClicked);
}

void SummaryWindowTest::buttonClicked()
{
    isClicked = true;
}

}
}

QTEST_MAIN(membermanagertest::gui::SummaryWindowTest)
#include "summarywindowtest.moc"
