#ifndef COUNTMEMBERSUMMARY_H
#define COUNTMEMBERSUMMARY_H

#include <QtCore>
#include <QPushButton>

#include "summaryhandler.h"

namespace ClubFrontend
{

class CountMemberSummary : public QObject
{
    Q_OBJECT

public:
    CountMemberSummary(SummaryHandler *aHandler, QObject *parent = 0);

private slots:
    void summaryResult();

private:
    QPushButton *countMemberButton;
    SummaryHandler *handler;
};

}

#endif // COUNTMEMBERSUMMARY_H
