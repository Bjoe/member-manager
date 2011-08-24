#include "debitsumsummary.h"

namespace ClubFrontend
{

DebitSumSummary::DebitSumSummary(SummaryHandler *aHandler, QObject *parent) :
    QObject(parent), handler(aHandler), debitSumButton(new QPushButton())
{
    debitSumButton->setObjectName(QString::fromUtf8("debitSumButton"));
    debitSumButton->setText(tr("Debit Summe"));

    connect(debitSumButton, SIGNAL(clicked(bool)), this, SLOT(summaryResult()));

    handler->addButton(debitSumButton);
}

void DebitSumSummary::summaryResult()
{
    QString result("foo");

    // TODO QVector< Member > MemberModel.getSelectedMembers();

    handler->showSummary(result);
}


}
