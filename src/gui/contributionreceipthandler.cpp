#include "contributionreceipthandler.h"

#include <QList>

#include "entity/member.h"
#include "entity/balance.h"
#include "dao/membertablemodel.h"
#include "dao/balancetablemodel.h"

namespace membermanager {
namespace gui {

ContributionReceiptHandler::ContributionReceiptHandler(QObject *parent) :
    QObject(parent)
{
}

QString ContributionReceiptHandler::showReceipt(QVariant memberId, int year)
{
    entity::Member *member = dao::MemberTableModel::findByMemberId(memberId);

    QString address;
    address.append(QString("%1 ").arg(member->firstname())).append(QString("%1 \\\\ \n").arg(member->name()));
    address.append(QString("%1 \\\\ \n").arg(member->street()));
    address.append(QString("%1 ").arg(member->zipCode())).append(QString("%1 \n\n").arg(member->city()));
    address.append(QString("%1 %2, %3, %4 %5 \n\n")
            .arg(member->firstname())
            .arg(member->name())
            .arg(member->street())
            .arg(member->zipCode())
            .arg(member->city()));

    QString timeRange = QString(tr("vom 01.01.%1 bis zum 31.12.%1")).arg(year);

    QList<entity::Balance *> balanceList = dao::BalanceTableModel::findContributionByMemberIdAndYear(memberId, year);

    QString contribution("\n");
    double sum = 0;
    foreach(entity::Balance *balance, balanceList) {
        QDate valuta = balance->valuta();
        double value = balance->value();
        contribution.append(QString("%1 & ").arg(valuta.toString("dd.MM.yyyy")));
        contribution.append(QString("%L1 Euro & ").arg(value, 7, 'f', 2, ' '));
        contribution.append(QString("%1 \\\\ \n").arg(balance->purpose()));
        sum += value;
    }
    balanceList.clear(); // TODO use "delete" to clear?

    contribution.append("\n");
    contribution.append(QString("Summe: %L1 Euro\n").arg(sum, 7, 'f', 2));

    QString content;
    content.append(QString("%1\n").arg(address));
    content.append(QString("%1\n").arg(timeRange));
    content.append(QString("%1\n").arg(contribution));

    return content;
}

} // namespace gui
} // namespace membermanager
