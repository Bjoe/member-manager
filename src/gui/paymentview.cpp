#include "paymentview.h"
#include "ui_paymentview.h"

#include <QString>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QTableWidget>
#include <QStringList>

#include "member.h"
#include "dao/memberdao.h"

#include "accounting/pay.h"

namespace membermanager
{
namespace gui
{

PaymentView::PaymentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaymentView)
{
    ui->setupUi(this);

    QString purpose = QDate::currentDate().toString("MMM");
    ui->lineEdit->setText(purpose);

    connect(ui->calculateButton, SIGNAL(clicked()), SLOT(calculate()));
    connect(ui->bookingButton, SIGNAL(clicked()), SLOT(memberCollection()));
}

PaymentView::~PaymentView()
{
    delete ui;
}

void PaymentView::calculate()
{
    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(5);

    QStringList headers;
    headers << tr("Nr.") << tr("Vorname") << tr("Name") << tr("Buchungstext") << ("Buchen");
    tableWidget->setHorizontalHeaderLabels(headers);

    dao::MemberDao memberDao;
    QList<Member> memberList = memberDao.findByDeleted(false);
    foreach(Member member, memberList) {
        int row  = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0,
                             createTextItem(QString::number(member.getMemberId())));
        tableWidget->setItem(row, 1,
                             createTextItem(member.getFirstname()));
        tableWidget->setItem(row, 2,
                             createTextItem(member.getName()));
        tableWidget->setItem(row, 3,
                             createTextItem(ui->lineEdit->text()));

        QTableWidgetItem *item = new QTableWidgetItem;
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setCheckState(Qt::Checked);
        tableWidget->setItem(row, 4, item);
    }
}

QTableWidgetItem *PaymentView::createTextItem(const QString aText)
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

    item->setText(aText);
    return item;
}

void PaymentView::memberCollection()
{
    QTableWidget* tableWidget = ui->tableWidget;
    int rowCount = tableWidget->rowCount();
    if(rowCount == 0) {
        return;
    }

    QDate date = QDate::currentDate();
    QSettings settings;
    QString bankName = settings.value("bank/name").toString();
    QString bankCode = settings.value("bank/code").toString();
    QString accountNumber = settings.value("bank/account").toString();

    membermanager::accounting::Pay pay(accountNumber, bankName, bankCode);

    dao::MemberDao memberDao;
    for(int row = 0; rowCount > row; ++row) {
        QTableWidgetItem *memberIdItem = tableWidget->item(row, 0);
        QTableWidgetItem *purposeItem = tableWidget->item(row, 3);
        QTableWidgetItem *bookingItem = tableWidget->item(row, 4);
        bool booking = false;
        if(bookingItem->checkState() == Qt::Checked) {
            booking = true;
        }
        QString memberId = memberIdItem->text();
        Member member = memberDao.findByMemberId(memberId.toInt());
        pay.payment(member, purposeItem->text() , date, booking);
    }

    QString filename = QString("DTAUS_%1").arg(date.toString(Qt::ISODate));
    QList<double> sum = pay.balancing(filename);

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

} // namespace gui
} // namespace membermanager
