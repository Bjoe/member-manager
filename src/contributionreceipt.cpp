
#include "contributionreceipt.h"

namespace membermanager
{

ContributionReceipt::ContributionReceipt(const QList<Member> &aMemberList) :
        memberList(aMemberList), writer(0)
{
}

ContributionReceipt::~ContributionReceipt()
{
}

QString ContributionReceipt::getTitle() const
{
    return QString("Spenden");
}

void ContributionReceipt::setWriter(SummaryWriter *aWriter)
{
    writer = aWriter;
}

void ContributionReceipt::handleHtmlText()
{
    writer->writeContent(QString("foo"));
}

}
