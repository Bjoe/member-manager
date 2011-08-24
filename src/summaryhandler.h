#ifndef SUMMARYHANDLER_H
#define SUMMARYHANDLER_H

#include <QString>
#include <QPushButton>

namespace ClubFrontend
{

class SummaryHandler
{

public:
    virtual ~SummaryHandler() {}

    virtual void showSummary(const QString &aText) = 0;
    virtual void addButton(QPushButton *aButton) = 0;
};

}

#endif // SUMMARYHANDLER_H
