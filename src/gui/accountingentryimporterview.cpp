#include "accountingentryimporterview.h"
#include "ui_accountingentryimporterview.h"

#include <QVariant>
#include <QString>
#include <QDate>
#include <QStringList>
#include <QTableWidgetItem>
#include <QTableWidget>

#include "gui/memberlistdelegate.h"

#include <QAbstractItemModel>

namespace membermanager
{
namespace gui
{

AccountingEntryImporterView::AccountingEntryImporterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountingEntryImporterView)
{
    ui->setupUi(this);

    QTableWidget *accountingEntryTable = ui->tableWidget;
    accountingEntryTable->setColumnCount(8);

    QStringList headerStringList;
    headerStringList << tr("Mitglieds Nr") << tr("Mitglied") << tr("Beitrag") << tr("Spende") << tr("CCC") << tr("Datum") << tr("Betrag") << tr("Transaction");
    accountingEntryTable->setHorizontalHeaderLabels(headerStringList);
    accountingEntryTable->setItemDelegateForColumn(1, new MemberListDelegate());

    accountingEntryTable->insertRow(0);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("0")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(0, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("ignore")));
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
    item->setData(Qt::DisplayRole, QVariant(QString("1000")));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 0, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("James T. Kirk")));
    accountingEntryTable->setItem(1, 1, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("15")));
    accountingEntryTable->setItem(1, 2, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("10")));
    accountingEntryTable->setItem(1, 3, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("5")));
    accountingEntryTable->setItem(1, 4, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QDate(2012,8,10)));
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    accountingEntryTable->setItem(1, 5, item);

    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, QVariant(QString("30")));
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

} // namespace gui
} // namespace membermanager
