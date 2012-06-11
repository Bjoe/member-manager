#include "summaryview.h"
#include "ui_summaryview.h"

#include "member.h"
#include "dao/memberdao.h"
#include "dao/contributiondao.h"
#include "dao/balancedao.h"

namespace membermanager
{
namespace gui
{

SummaryView::SummaryView(QWidget *aParent) :
    QWidget(aParent),
    ui(new Ui::SummaryView)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(calculate()));
}

SummaryView::~SummaryView()
{
    delete ui;
}

void SummaryView::calculate()
{
    QDate date = QDate::currentDate();

    dao::MemberDao memberDao(QSqlDatabase::database());
    dao::ContributionDao contributionDao(QSqlDatabase::database());
    dao::BalanceDao balanceDao(QSqlDatabase::database());

    QMap<double, double> sumMap;
    QMap<double, int> countMember;

    double totalCash = 0;
    double totalDonation = 0;
    double totalSaldo = 0;
    double totalCollection = 0;
    int totalMembers = 0;
    int totalMemberCollection = 0;
    int totalMemberDonation = 0;

    QList<Member> memberList = memberDao.findByDeleted(false);
    foreach(Member member, memberList) {
         int memberId = member.getMemberId();
         ++totalMembers;

        QList<accounting::BalanceEntry> balanceList = balanceDao.findByMemberId(memberId);
        accounting::BalanceEntry balanceEntry;
        foreach(balanceEntry, balanceList) {
            totalSaldo += balanceEntry.getValue();
        }

        accounting::ContributionEntry contributionEntry = contributionDao.findByMemberIdWithPointInTime(memberId, date);
        double donation = contributionEntry.getDonation();
        if(donation > 0) {
            ++totalMemberDonation;
        }
        totalDonation += donation;
        double fee = contributionEntry.getFee();
        totalCash += fee;

        if(member.isCollection()) {
            ++totalMemberCollection;
            totalCollection = totalCollection + fee + donation;
        }

        if(sumMap.contains(fee)) {
            double sum = sumMap.value(fee);
            sum += fee;
            sumMap.insert(fee, sum);
            int count = countMember.value(fee);
            ++count;
            countMember.insert(fee, count);
        } else {
            sumMap.insert(fee, fee);
            countMember.insert(fee, 1);
        }

    }
    totalCash += totalDonation;

    ui->totalCash->setText(QString("%L1 Euro").arg(totalCash, 7, 'f', 2));
    ui->totalDonation->setText(QString("%L1 Euro").arg(totalDonation, 7, 'f', 2));
    ui->totalCollection->setText(QString("%L1 Euro").arg(totalCollection, 7, 'f', 2));

    ui->totalSaldo->setText(QString("%L1 Euro").arg(totalSaldo, 7, 'f', 2));

    ui->totalMembers->setText(QString::number(totalMembers));
    ui->totalMemberCollection->setText(QString::number(totalMemberCollection));
    ui->totalMemberDonation->setText(QString::number(totalMemberDonation));

    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(3);

    QStringList headers;
    headers << tr("Anzahl") << tr("Beitrag") << tr("Gesamt");
    tableWidget->setHorizontalHeaderLabels(headers);

    foreach(double feeKey, sumMap.keys()) {
        int row  = tableWidget->rowCount();
        tableWidget->insertRow(row);

        QTableWidgetItem *itemCount = new QTableWidgetItem;
        itemCount->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemCount->setText(QString::number(countMember.value(feeKey)));
        tableWidget->setItem(row, 0, itemCount);

        QTableWidgetItem *itemFee = new QTableWidgetItem;
        itemFee->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemFee->setText(QString("%L1 Euro").arg(feeKey, 7, 'f', 2));
        tableWidget->setItem(row, 1, itemFee);

        QTableWidgetItem *itemTotal = new QTableWidgetItem;
        itemTotal->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        itemTotal->setText(QString("=  %L1 Euro").arg(sumMap.value(feeKey), 7, 'f', 2));
        tableWidget->setItem(row, 2, itemTotal);
    }
}

}
}
