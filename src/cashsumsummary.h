#ifndef CASHSUMSUMMARY_H
#define CASHSUMSUMMARY_H

#include <QString>

#include "summaryhandler.h"
#include "summarywriter.h"
#include "member.h"

namespace membermanager
{

class CashSumSummary : public SummaryHandler
{
public:
    CashSumSummary(const QList<Member> &aMemberList);

    virtual QString getTitle() const;
    virtual void setWriter(SummaryWriter *aWriter);

    virtual void handleHtmlText();

private:
    const QList<Member> memberList;
    SummaryWriter *writer;
};

}

#endif // CASHSUMSUMMARY_H
