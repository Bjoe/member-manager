#ifndef SUMMARYHANDLERMOCK_H
#define SUMMARYHANDLERMOCK_H

#include <QPushButton>
#include <QString>

#include "summaryhandler.h"

namespace membermanagertest
{
namespace util
{

class SummaryHandlerMock : public membermanager::SummaryHandler
{

public:
    SummaryHandlerMock();
    virtual ~SummaryHandlerMock();

    virtual void addButton(QPushButton *aButton);
    virtual void showSummary(const QString &aText);

    QPushButton *getPushButton() const;
    QString getText() const;

private:
    QPushButton *button;
    QString text;
};

}
}

#endif // SUMMARYHANDLERMOCK_H
