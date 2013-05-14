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
    address.append(QString("%1 ").arg(member.getFirstname())).append(QString("%1 \\\\ \n").arg(member.getName()));
    address.append(QString("%1 \\\\ \n").arg(member.getStreet()));
    address.append(QString("%1 ").arg(member.getZipCode())).append(QString("%1 \n\n").arg(member.getCity()));
    address.append(QString("%1 %2, %3, %4 %5 \n\n")
            .arg(member.getFirstname())
            .arg(member.getName())
            .arg(member.getStreet())
            .arg(member.getZipCode())
            .arg(member.getCity()));

    QString timeRange = QString(tr("vom 01.01.%1 bis zum 31.12.%1")).arg(year);

    QString contribution("\n");
    double sum = 0;
    accounting::BalanceEntry balance;
    foreach(balance, balanceList) {
        QDate valuta = balance.getValuta();
        double value = balance.getValue();
        contribution.append(QString("%1 & ").arg(valuta.toString("dd.MM.yyyy")));
        contribution.append(QString("%L1 Euro & ").arg(value, 7, 'f', 2, ' '));
        contribution.append(QString("%1 \\\\ \n").arg(balance.getPurpose()));
        sum += value;
    }
    contribution.append("\n");
    contribution.append(QString("Summe: %L1 Euro\n").arg(sum, 7, 'f', 2));

    QString content;
    content.append(QString("%1\n").arg(address));
    content.append(QString("%1\n").arg(timeRange));
    content.append(QString("%1\n").arg(contribution));

    ui.textEdit->setText(content);
}

} // namespace gui
} // namespace membermanager
