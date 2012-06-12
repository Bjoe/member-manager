#include "gui/mainwindow.h"

#include "gui/summarywindow.h"
#include "gui/memberdetailview.h"
#include "gui/memberdebtview.h"
#include "gui/summaryview.h"

#include "cashsumsummary.h"
#include "debitsumsummary.h"
#include "accounting/pay.h"

namespace membermanager
{
namespace gui
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(), listWidget(0), stackedLayout(0)
{
    ui.setupUi(this);

    listWidget = new QListWidget();
    listWidget->addItem(tr("Gesamt Ueberblick"));
    listWidget->addItem(tr("Mitglieder"));
    listWidget->addItem(tr("geloeschte Mitglieder"));
    listWidget->addItem(tr("Mitglieder Schulden"));

    stackedLayout = new QStackedWidget();
    stackedLayout->addWidget(new SummaryView(this));
    stackedLayout->addWidget(new MemberDetailView(false, this));
    stackedLayout->addWidget(new MemberDetailView(true, this));
    stackedLayout->addWidget(new MemberDebtView(this));

    ui.horizontalLayout->addWidget(listWidget);
    ui.horizontalLayout->addWidget(stackedLayout, 1);

    connect(listWidget, SIGNAL(currentRowChanged(int)),
            stackedLayout, SLOT(setCurrentIndex(int)));

    listWidget->setCurrentRow(0);

    connect(ui.actionSummary, SIGNAL(triggered()), SLOT(managerSummary()));
    connect(ui.actionMemberCollectionWithBooking, SIGNAL(triggered()), SLOT(memberCollectionWithBooking()));
    connect(ui.actionMemberCollectionWithoutBooking, SIGNAL(triggered()), SLOT(memberCollectionWithoutBooking()));
}



void MainWindow::managerSummary()
{
    dao::MemberDao dao;
    QList<Member> memberList = dao.findByDeleted(false);
    CashSumSummary cashSum(memberList);
    DebitSumSummary debitSum(memberList);

    SummaryWindow summaryWindow(this);
    summaryWindow.addSummary(&cashSum);
    summaryWindow.addSummary(&debitSum);
    summaryWindow.exec();
}

void MainWindow::memberCollectionWithBooking()
{
    memberCollection(true);
}

void MainWindow::memberCollectionWithoutBooking()
{
    memberCollection(false);
}

void MainWindow::memberCollection(bool isBooking)
{
    QDate date = QDate::currentDate();

    QSettings settings;
    QString bankName = settings.value("bank/name").toString();
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();

    membermanager::accounting::Pay pay(accountNumber, bankName, bankCode);

    dao::MemberDao dao;
    QList<Member> memberList = dao.findByDeleted(false);
    foreach(const Member member, memberList) {
       pay.payment(member, date.toString("MMM"), date, isBooking);
    }

    QString filename = QString("DTAUS_%1.txt").arg(date.toString(Qt::ISODate));
    QList<double> sum = pay.balancing("DTAUS0.txt");

    filename = QString("sum-%1.csv").arg(date.toString(Qt::ISODate));
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << date.toString("dd.MM.yyyy") << ";" << "Einzug 011" << ";" << "011 Mitgliedsbeitraege" << ";" << sum[0] << "\n";
    out << date.toString("dd.MM.yyyy") << ";" << "Einzug 012" << ";" << "012 Spenden" << ";" << sum[1] << "\n";
    file.close();
}

}
}
