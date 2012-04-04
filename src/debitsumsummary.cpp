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
            htmlText.append("<br><br><br>");
            htmlText.append(tr("To:"));
            htmlText.append(0x20);
            htmlText.append(member.getEmail());
            htmlText.append("<br><br>");
            htmlText.append(tr("Subject: Chaosdorf Mitgliedsbeitrag Kontostand"));
            htmlText.append("<br><br>");
            htmlText.append(tr("Hallo"));
            htmlText.append(0x20);
            htmlText.append(member.getFirstname());
            htmlText.append(",<br>");
            htmlText.append(tr("leider weist dein Mitlgiedskontostand ein Sollwert von"));
            htmlText.append(0x20);
            htmlText.append(QString("%1").arg(saldo));
            htmlText.append(0x20);
            htmlText.append(tr("auf."));
            htmlText.append("<br>");
            htmlText.append(tr("Bitte zahle uns den ausstehenden Beitrag von"));
            htmlText.append(0x20);
            htmlText.append(QString("%1").arg(saldo * -1));
            htmlText.append(0x20);
            htmlText.append(tr("EUR auf"));
            htmlText.append("<br>");
            htmlText.append(tr("folgendes Vereins Konto ein:"));
            htmlText.append("<br>");
            htmlText.append(tr("Name: Chaosdorf e.V."));
            htmlText.append("<br>");
            htmlText.append(tr("Konto Nr.: 21057476"));
            htmlText.append("<br>");
            htmlText.append(tr("BLZ: 300 501 10"));
            htmlText.append("<br>");
            htmlText.append(tr("Bank: Stadtsparkasse Duesseldorf"));
            htmlText.append("<br><br>");
            htmlText.append(tr("Als Referenz bitte folgendes Eintragen:"));
            htmlText.append("<br>");
            htmlText.append(tr("Mitgliedsnr, dein Vorname und Nachname Mitgliedsschulden"));
            htmlText.append("<br>");
            htmlText.append(tr("Also deine Referenz:"));
            htmlText.append("<br>");
            htmlText.append(QString("%1").arg(member.getMemberId()));
            htmlText.append(0x20);
            htmlText.append(member.getFirstname());
            htmlText.append(0x20);
            htmlText.append(member.getName());
            htmlText.append(0x20);
            htmlText.append(tr("Mitgliedsschulden"));
            htmlText.append("<br><br>");
            htmlText.append(tr("Sollte es Probleme oder Fragen geben, dann wende dich bitte"));
            htmlText.append("<br>");
            htmlText.append(tr("schnellstmoeglich an den Chaosdorf Vorstand"));
            htmlText.append("<br>");
            htmlText.append(tr("Chaosdorf Vorstand <vorstand@chaosdorf.de>"));
            htmlText.append("<br>");
            htmlText.append(tr("Diese Email wurde automatisch generiert und verschickt"));
            htmlText.append("<br><br><br>");
            writer->writeContent(htmlText);

            saldoSum += saldo;
        }
    }
    QString htmlTextSaldoSum = QString(tr("<br><br>Gesamt Saldo: %1<br>")).arg(saldoSum);
    writer->writeContent(htmlTextSaldoSum);
}


}
