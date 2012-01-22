#ifndef SUMMARYHANDLER_H
#define SUMMARYHANDLER_H

#include <QObject>
#include <QString>
#include "summarywriter.h"

namespace membermanager
{

class SummaryHandler : public QObject
{
    Q_OBJECT

public:
    virtual ~SummaryHandler() {}

    virtual QString getTitle() const = 0;
    virtual void setWriter(SummaryWriter *aWriter) = 0;

public slots:
    virtual void handleHtmlText() = 0;
};

}

#endif // SUMMARYHANDLER_H
