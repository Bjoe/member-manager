#ifndef DEBITSUMSUMMARY_H
#define DEBITSUMSUMMARY_H

#include <QtCore>
#include <QPushButton>

#include "summaryhandler.h"

namespace ClubFrontend
{

class DebitSumSummary : public QObject
{
    Q_OBJECT

public:
    DebitSumSummary ( SummaryHandler *aHandler, QObject* parent = 0 );

private slots:
    void summaryResult();

private:
    SummaryHandler *handler;
    QPushButton *debitSumButton;
};

}

#endif // DEBITSUMSUMMARY_H
