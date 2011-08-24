#ifndef SUMMARYHANDLERMOCK_H
#define SUMMARYHANDLERMOCK_H

#include <QPushButton>
#include <QString>

#include "summaryhandler.h"

namespace ClubFrontendTest
{
namespace Utils
{

class SummaryHandlerMock : public ClubFrontend::SummaryHandler
{

public:
    SummaryHandlerMock();
    virtual ~SummaryHandlerMock();

    virtual void addButton ( QPushButton* aButton );
    virtual void showSummary ( const QString& aText );

    QPushButton* getPushButton() const;
    QString getText() const;

private:
    QPushButton *button;
    QString text;
};

}
}

#endif // SUMMARYHANDLERMOCK_H
