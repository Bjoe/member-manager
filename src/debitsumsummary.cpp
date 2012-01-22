#include "debitsumsummary.h"

namespace membermanager
{

DebitSumSummary::DebitSumSummary(const QList<Member> &aMemberList) :
    memberList(aMemberList), writer(0)
{
}

QString DebitSumSummary::getTitle() const
{
    return QString("Saldo");
}

void DebitSumSummary::setWriter(SummaryWriter *aWriter)
{
    writer = aWriter;
}

void DebitSumSummary::handleHtmlText()
{
    double saldoSum = 0;
    foreach(Member member, memberList) {
        double saldo = member.getSaldoModel().amount();
        if(saldo < 0) {
            QString htmlText;
            htmlText.append(tr("To: "));
            htmlText.append(0x20);
            htmlText.append(member.getEmail());
            htmlText.append("<br>");
            htmlText.append(tr("Name "));
            htmlText.append(0x20);
            htmlText.append(member.getName());
            htmlText.append("<br>");
            htmlText.append(tr("Mitgliedschulden"));
            htmlText.append(0x20);
            htmlText.append(QString("%1").arg(saldo));
            writer->writeContent(htmlText);

            saldoSum += saldo;
        }
    }
    QString htmlTextSaldoSum = QString(tr("<br><br>Gesamt Saldo: %1<br>")).arg(saldoSum);
    writer->writeContent(htmlTextSaldoSum);
}


}
