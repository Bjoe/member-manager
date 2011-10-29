#include "testutil/summaryhandlermock.h"

namespace membermanagertest
{
namespace util
{

SummaryHandlerMock::SummaryHandlerMock() :
    button(0), text("")
{

}

SummaryHandlerMock::~SummaryHandlerMock()
{

}

void SummaryHandlerMock::addButton(QPushButton *aButton)
{
    button = aButton;
}

void SummaryHandlerMock::showSummary(const QString &aText)
{
    text = aText;
}

QPushButton *SummaryHandlerMock::getPushButton() const
{
    return button;
}

QString SummaryHandlerMock::getText() const
{
    return text;
}

}
}
