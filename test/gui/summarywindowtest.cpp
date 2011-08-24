#include "summarywindowtest.h"

#include "gui/summarywindow.h"

#include <QtCore/QtCore>
#include <QtGui>

namespace ClubFrontendTest
{
namespace Gui
{

SummaryWindowTest::SummaryWindowTest() : isClicked(false)
{}


void SummaryWindowTest::testShowSummary()
{
    ClubFrontend::Gui::SummaryWindow summary;

    summary.showSummary("foo");

    const QTextEdit *textEdit = summary.findChild<QTextEdit *> ("textEdit");

    QCOMPARE(textEdit->toPlainText(), QString("foo"));
}

void SummaryWindowTest::testAddButton()
{
    isClicked = false;
    ClubFrontend::Gui::SummaryWindow summary;

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

QTEST_MAIN(ClubFrontendTest::Gui::SummaryWindowTest)
#include "summarywindowtest.moc"
