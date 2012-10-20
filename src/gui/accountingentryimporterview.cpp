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
    ui(new Ui::AccountingEntryImporterView),
    balancePersister(0)
{
    ui->setupUi(this);

    QTableWidget *accountingEntryTable = ui->tableWidget;
    accountingEntryTable->setColumnCount(9);

    QStringList headerStringList;
    headerStringList << tr("Mitglieds Nr")
                     << tr("Mitglied")
                     << tr("Beitrag")
                     << tr("Spende")
                     << tr("CCC")
                     << tr("Datum")
                     << tr("Betrag")
                     << tr("Transaction")
                     << tr("Booked");
    accountingEntryTable->setHorizontalHeaderLabels(headerStringList);
    accountingEntryTable->setItemDelegateForColumn(1, new MemberListDelegate());

    balancePersister = new accounting::BalancePersister(accountingEntryTable, this);
    connect(ui->bookingButton, SIGNAL(clicked()), balancePersister, SLOT(booking()));
    connect(ui->importButton, SIGNAL(clicked()), SLOT(importTransactions()));
}

AccountingEntryImporterView::~AccountingEntryImporterView()
{
    delete balancePersister;
    delete ui;
}

void AccountingEntryImporterView::importTransactions()
{
    // TODO only for tests
    QTableWidget *accountingEntryTable = ui->tableWidget;
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

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    accountingEntryTable->setItem(0, 8, item);


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

    item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);
    accountingEntryTable->setItem(1, 8, item);
}

} // namespace gui
} // namespace membermanager
