#ifndef CASHSUMSUMMARY_H
#define CASHSUMSUMMARY_H

#include <QtCore>
#include <QPushButton>

#include "summaryhandler.h"

namespace membermanager
{

class CashSumSummary : public QObject
{
    Q_OBJECT

public:
    CashSumSummary(SummaryHandler *aHandler, QObject *parent = 0);

private slots:
    void summaryResult();

private:
    SummaryHandler *handler;
    QPushButton *cashSumButton;
};

}

#endif // CASHSUMSUMMARY_H
