#include "cashsumsummary.h"

namespace membermanager
{

CashSumSummary::CashSumSummary(const QList<Member> &aMemberList) :
    memberList(aMemberList), writer(0)
{
}

QString CashSumSummary::getTitle() const
{
    return QString("Einahmen");
}

void CashSumSummary::setWriter(SummaryWriter *aWriter)
{
    writer = aWriter;
}

void CashSumSummary::handleHtmlText()
{
    QMap<double, double> sumMap;
    QMap<double, int> countMember;
    double total = 0;
    double donationTotal = 0;
    double saldoSum = 0;
    int memberSum = 0;
    int memberCollection = 0;
    double totalCollection = 0;
    foreach(Member member, memberList) {
        memberSum++;

        double donation = member.getMemberContribution().getDonation();
        donationTotal += donation;
        double saldo = member.getSaldoModel().amount();
        saldoSum += saldo;
        double fee = member.getMemberContribution().getFee();
        total += fee;

        if(member.isCollection()) {
            memberCollection++;
            totalCollection = totalCollection + fee + donation;
        }

        if(sumMap.contains(fee)) {
            double sum = sumMap.value(fee);
            sum += fee;
            sumMap.insert(fee, sum);
            int count = countMember.value(fee);
            count++;
            countMember.insert(fee, count);
        } else {
            sumMap.insert(fee, fee);
            countMember.insert(fee, 1);
        }

    }
    total += donationTotal;

    foreach(double feeKey, sumMap.keys()) {
        QString htmlText = QString(tr("Anzahl %1 * Beitrag %2 Gesamt = %3<br>"))
                .arg(countMember.value(feeKey)).arg(feeKey).arg(sumMap.value(feeKey));
        writer->writeContent(htmlText);
    }
    QString htmlTextDonation = QString(tr("<br>Gesamt Spenden: %1<br><br>")).arg(donationTotal);
    writer->writeContent(htmlTextDonation);
    QString htmlTextSum = QString(tr("Gesamt Mitglieder: %1 Einahmen: %2<br><br>")).arg(memberSum).arg(total);
    writer->writeContent(htmlTextSum);
    QString htmlTextCollection = QString(tr("Gesamt Einzuege Mitglieder: %1 Einahmen: %2<br><br>")).arg(memberCollection).arg(totalCollection);
    writer->writeContent(htmlTextCollection);
    QString htmlTextSaldoSum = QString(tr("Gesamt Saldo: %1<br>")).arg(saldoSum);
    writer->writeContent(htmlTextSaldoSum);
}

}
