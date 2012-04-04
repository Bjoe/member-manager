#ifndef CONTRIBUTIONRECEIPT_H_
#define CONTRIBUTIONRECEIPT_H_

#include <QString>
#include <QList>

#include "summaryhandler.h"
#include "summarywriter.h"
#include "member.h"

namespace membermanager
{

class ContributionReceipt : public SummaryHandler
{
public:
    ContributionReceipt(const QList<Member> &aMemberList);
    virtual ~ContributionReceipt();

    virtual QString getTitle() const;
    virtual void setWriter(SummaryWriter *aWriter);

    virtual void handleHtmlText();

private:
    QList<Member> memberList;
    SummaryWriter *writer;
};

}

#endif /* CONTRIBUTIONRECEIPT_H_ */
