#include "accountingentryimporterview.h"
#include "ui_accountingentryimporterview.h"

#include <QVariant>
#include <QString>
#include <QDate>
#include <QStringList>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QAbstractItemModel>

#include "gui/memberlistdelegate.h"
#include "dao/balancedao.h"
#include "accounting/balanceentry.h"

namespace membermanager
{
namespace gui
{

AccountingEntryImporterView::AccountingEntryImporterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountingEntryImporterView)
{
    ui->setupUi(this);

    connect(ui->bookingButton, SIGNAL(clicked()), SLOT(bookBalance()));

    QTableWidget *accountingEntryTable = ui->tableWidget;
    accountingEntryTable->setColumnCount(8);

    QStringList headerStringList;
    headerStringList << tr("Mitglieds Nr") << tr("Mitglied") << tr("Beitrag") << tr("Spende") << tr("CCC") << tr("Datum") << tr("Betrag") << tr("Transaction");
    accountingEntryTable->setHorizontalHeaderLabels(headerStringList);
    accountingEntryTable->setItemDelegateForColumn(1, new MemberListDelegate());

    // TODO only for tests
    accountingEntryTable->insertRow(0);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("-")));
    accountingEntryTable->setItem(0, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(0, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(0, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(0, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,8,9)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("530")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Miete")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 7, item);


    accountingEntryTable->insertRow(1);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1025")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Kirk")));
    accountingEntryTable->setItem(1, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("99")));
    accountingEntryTable->setItem(1, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("1.5")));
    accountingEntryTable->setItem(1, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    accountingEntryTable->setItem(1, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::UserRole, QVariant(123456));
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,8,10)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("100.5")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 6, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("Mitgliedsbeitrag")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 7, item);

}

AccountingEntryImporterView::~AccountingEntryImporterView()
{
    delete ui;
}

void AccountingEntryImporterView::bookBalance()
{
    dao::BalanceDao balanceDao;

    QTableWidget *accountingEntryTable = ui->tableWidget;
    for(int i = 0; i < accountingEntryTable->rowCount(); ++i) {
        int memberId = getData(i, 0).toInt();

        if(memberId != 0) {
            float fee = getData(i, 2).toFloat();
            float donation = getData(i, 3).toFloat();
            float additionalFee = getData(i, 4).toFloat();

            float value = getData(i, 6).toFloat();
            if((fee + donation + additionalFee) == value) {
                accounting::BalanceEntry balanceEntry(memberId);

                QVariant date = getData(i, 5);
                balanceEntry.setValuta(date.toDate());

                QTableWidgetItem *item = ui->tableWidget->item(i, 5);
                int cashKey = item->data(Qt::UserRole).toInt();
                balanceEntry.setCashKey(cashKey);

                balanceEntry.setInfo("Automatische Buchung");

                if(fee != 0) {
                    QVariant purpose = getData(i, 7);
                    balanceEntry.setPurpose(purpose.toString());
                    balanceEntry.setValue(fee);
                    balanceEntry.setAccount(11);
                    balanceDao.saveRecord(balanceEntry);
                }

                if(donation != 0) {
                    balanceEntry.setPurpose("Spende");
                    balanceEntry.setValue(donation);
                    balanceEntry.setAccount(12);
                    balanceDao.saveRecord(balanceEntry);
                }

                if(additionalFee != 0) {
                    balanceEntry.setPurpose("Zusaetzlicher Beitrag");
                    balanceEntry.setValue(additionalFee);
                    balanceEntry.setAccount(4);
                    balanceDao.saveRecord(balanceEntry);
                }
                // TODO Tabelle eintrag sperren
            } // else
            // TODO Tabellen Eintrag rot faerben. Summe stimmt nicht!
        }
    }
}

QVariant AccountingEntryImporterView::getData(int aRow, int aColumn)
{
    QTableWidgetItem *item = ui->tableWidget->item(aRow, aColumn);
    return item->data(Qt::DisplayRole);
}

} // namespace gui
} // namespace membermanager
