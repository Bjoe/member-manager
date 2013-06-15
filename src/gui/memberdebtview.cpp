#include "memberdebtview.h"
#include "ui_memberdebtview.h"

#include "member.h"
#include "accounting/balanceentry.h"
#include "dao/memberdao.h"
#include "dao/balancedao.h"

namespace membermanager
{
namespace gui
{

MemberDebtView::MemberDebtView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemberDebtView)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(calculate()));
}

MemberDebtView::~MemberDebtView()
{
    delete ui;
}

void MemberDebtView::calculate()
{
    ui->textEdit->clear();

    dao::MemberDao memberDao(QSqlDatabase::database());
    dao::BalanceDao balanceDao(QSqlDatabase::database());

    double totalDebit = 0;
    QList<Member> memberList = memberDao.findByDeleted(false);
    foreach(Member member, memberList) {
        int memberId = member.getMemberId();
        QList<accounting::BalanceEntry> balanceList = balanceDao.findByMemberId(memberId);
        double debit = 0;
        accounting::BalanceEntry balanceEntry;
        foreach(balanceEntry, balanceList) {
            if((balanceEntry.getAccount() == 11) || (balanceEntry.getAccount() == 4)
                    || (balanceEntry.getAccount() == -11) || (balanceEntry.getAccount() == -4)) {
                debit += balanceEntry.getValue();
            }
        }

        if(debit < 0) {
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
            htmlText.append(",<br><br>");
            htmlText.append(tr("leider weist dein Mitgliedskontostand ein Sollwert von"));
            htmlText.append(0x20);
            htmlText.append(QString("%L1").arg(debit, 4, 'f', 2));
            htmlText.append(0x20);
            htmlText.append(tr("EUR auf."));
            htmlText.append("<br>");
            htmlText.append(tr("Bitte zahle uns den ausstehenden Beitrag von"));
            htmlText.append(0x20);
            htmlText.append(QString("%L1").arg((debit * -1), 4, 'f', 2));
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
            htmlText.append(QString("%1").arg(memberId));
            htmlText.append(0x20);
            htmlText.append(member.getFirstname());
            htmlText.append(0x20);
            htmlText.append(member.getName());
            htmlText.append(0x20);
            htmlText.append(tr("ausstehenden Mitgliedsbeitraege"));
            htmlText.append("<br><br>");
            htmlText.append(tr("Sollte es Probleme oder Fragen geben, dann wende dich bitte"));
            htmlText.append("<br>");
            htmlText.append(tr("schnellstmoeglich an den Chaosdorf Vorstand"));
            htmlText.append("<br>");
            htmlText.append(tr("Chaosdorf Vorstand <vorstand@chaosdorf.de>"));
            htmlText.append("<br><br>");
            htmlText.append(tr("Diese Email wurde automatisch generiert und verschickt"));
            htmlText.append("<br><br><br>");
            ui->textEdit->insertHtml(htmlText);

            totalDebit += debit;
        }
    }
    QString htmlTextTotalDebit = QString(tr("<br><br>Gesamt Saldo: %1<br>")).arg(totalDebit);
    ui->textEdit->insertHtml(htmlTextTotalDebit);
}

} // namespace gui
} // namespace membermanager
