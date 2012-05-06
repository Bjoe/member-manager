#include "contributionreceiptdialog.h"

#include <QDate>

#include "dao/balancedao.h"
#include "dao/memberdao.h"

namespace membermanager
{
namespace gui
{

ContributionReceiptDialog::ContributionReceiptDialog(int aMemberId, QWidget *parent) :
    QDialog(parent), ui(), memberId(aMemberId)
{
    ui.setupUi(this);

    QString title = QString(tr("Member Id: %1")).arg(memberId);
    setWindowTitle(title);

    int year = QDate::currentDate().year();
    ui.yearSpinBox->setValue(year - 1);
    ui.yearSpinBox->setRange(2000, year);

    connect(ui.showButton, SIGNAL(clicked()), SLOT(showContribution()));
    connect(ui.buttonBox, SIGNAL(rejected()), SLOT(close()));
}

ContributionReceiptDialog::~ContributionReceiptDialog()
{
}

void ContributionReceiptDialog::showContribution()
{
    dao::MemberDao memberDao;
    Member member = memberDao.findByMemberId(memberId);

    int year = ui.yearSpinBox->value();

    dao::BalanceDao balanceDao;
    QList<accounting::BalanceEntry> balanceList = balanceDao.findContributionByMemberIdAndYear(memberId, year);


    QString address;
    address.append(QString("%1 ").arg(member.getFirstname())).append(QString("%1<br>").arg(member.getName()));
    address.append(QString("%1<br>").arg(member.getStreet()));
    address.append(QString("%1 ").arg(member.getZipCode())).append(QString("%1<br>").arg(member.getCity()));

    QString timeRange = QString(tr("vom 01.01.%1 bis zum 31.12.%1")).arg(year);

    QString contribution = QString("<table>");
    double sum = 0;
    accounting::BalanceEntry balance;
    foreach(balance, balanceList) {
        contribution.append("<tr>");
        QDate valuta = balance.getValuta();
        double value = balance.getValue();
        contribution.append(QString("<td>%1 /</td>").arg(valuta.toString("dd.MM.yyyy")));
        contribution.append(QString("<td align=\"right\">%L1 Euro / </td>").arg(value, 7, 'f', 2, ' '));
        contribution.append(QString("<td>%1</td>").arg(balance.getPurpose()));
        contribution.append("</tr>");
        sum += value;
    }
    contribution.append("</table>");
    contribution.append(QString("<br>Summe: %L1 Euro").arg(sum, 7, 'f', 2));

    QString content;
    content.append(QString("%1<br>").arg(address));
    content.append(QString("%1<br><br>").arg(timeRange));
    content.append(QString("%1<br>").arg(contribution));

    ui.textEdit->setHtml(content);
}

} // namespace gui
} // namespace membermanager
