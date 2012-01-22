#ifndef DEBITSUMSUMMARY_H
#define DEBITSUMSUMMARY_H

#include <QString>
#include <QList>

#include "summaryhandler.h"
#include "summarywriter.h"
#include "member.h"

namespace membermanager
{

class DebitSumSummary : public SummaryHandler
{

public:
    DebitSumSummary(const QList<Member> &aMemberList);

    virtual QString getTitle() const;
    virtual void setWriter(SummaryWriter *aWriter);

    virtual void handleHtmlText();

private:
    QList<Member> memberList;
    SummaryWriter *writer;
};

}

#endif // DEBITSUMSUMMARY_H
