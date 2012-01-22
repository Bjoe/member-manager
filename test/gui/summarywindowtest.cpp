#include "summarywindowtest.h"

#include "gui/summarywindow.h"

#include <QtCore/QtCore>
#include <QtGui>

#include "summarywriter.h"
#include "summaryhandler.h"

namespace membermanagertest
{
namespace gui
{

void SummaryWindowTest::testShowSummary()
{
    membermanager::gui::SummaryWindow summary;

    class : public membermanager::SummaryHandler
    {
    public:
        bool isWriter;
        bool isClick;
        membermanager::SummaryWriter *writer;

        virtual QString getTitle() const
        {
            return QString("foo");
        }

        virtual void setWriter(membermanager::SummaryWriter *aWriter)
        {
            writer = aWriter;
            isWriter = true;
        }

        virtual void handleHtmlText()
        {
            isClick = true;
            writer->writeContent("bar");
        }
    } testSummary;

    testSummary.isClick = false;
    testSummary.isWriter = false;

    summary.addSummary(&testSummary);

    QVERIFY(testSummary.isWriter == true);

    QPushButton *button = summary.findChild<QPushButton *>("foo");
    QTest::mouseClick(button, Qt::LeftButton);
    QVERIFY(testSummary.isClick == true);

    const QTextEdit *textEdit = summary.findChild<QTextEdit *> ("textEdit");
    QCOMPARE(textEdit->toPlainText(), QString("bar"));
}

}
}

QTEST_MAIN(membermanagertest::gui::SummaryWindowTest)
#include "summarywindowtest.moc"
