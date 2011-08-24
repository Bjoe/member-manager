#include "contributionmodel.h"

#include "model/databasestructure.h"
#include "model/tabledao.h"

namespace ClubFrontend
{
namespace Model
{

ContributionModel::ContributionModel(const QSqlDatabase &aDb) :
    model(new QSqlTableModel(this, aDb)), record(), memberId(0)
{
    model->setObjectName(ContributionTable::TABLENAME);
    record = model->record(0);

    model->setTable(ContributionTable::TABLENAME);
    model->setHeaderData(ContributionTable::Fee, Qt::Horizontal, tr("Beitrag"));
    model->setHeaderData(ContributionTable::Donation, Qt::Horizontal, tr("Spende"));
    model->setHeaderData(ContributionTable::ValidFrom, Qt::Horizontal, tr("Gültig ab:"));
    model->setHeaderData(ContributionTable::Info, Qt::Horizontal, tr("Info"));
}

ContributionModel::~ContributionModel()
{
}

//! \todo Refactor selectMemberId
void ContributionModel::setMemberId(const int aMemberId)
{
    QString columname = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    QString filter = QString(columname + " = %1").arg(aMemberId);
    model->setFilter(filter);
    model->setSort(ContributionTable::ValidFrom, Qt::DescendingOrder);
    refresh();
    memberId = aMemberId;
}

int ContributionModel::insertMemberId(const QVariant &aMemberId)
{
    model->setFilter("");
    model->select();
    Model::TableDao tableDao;
    int row = tableDao.insertNewRow(model, ContributionTable::MemberId, aMemberId);
    setMemberId(aMemberId.toInt());
    return row;
}

void ContributionModel::refresh()
{
    model->select();
    record = model->record(0);
}

QString ContributionModel::getDonation() const
{
    return getDonationValue().toString();
}

QVariant ContributionModel::getDonationValue() const
{
    return record.value(ContributionTable::Donation);
}

QString ContributionModel::getFee() const
{
    return getFeeValue().toString();
}

QVariant ContributionModel::getFeeValue() const
{
    return record.value(ContributionTable::Fee);
}

QString ContributionModel::getInfo() const
{
    return getInfoValue().toString();
}

QVariant ContributionModel::getInfoValue() const
{
    return record.value(ContributionTable::Info);
}


// TODO Refactor: In DAO Klasse Refactoren
void ContributionModel::submit(const QString &aFee, const QString &aDonation, const QString &anInfo)
{
    QString fee = getFee();
    QString donation = getDonation();

    if(fee.compare(aFee) != 0 || donation.compare(aDonation) != 0) {
        QSqlRecord newRecord = model->record();
        newRecord.setValue(ContributionTable::MemberId, memberId);
        newRecord.setValue(ContributionTable::Fee, QVariant(aFee));
        newRecord.setValue(ContributionTable::Donation, QVariant(aDonation));
        newRecord.setValue(ContributionTable::Info, QVariant(anInfo));
        QDate date = QDate::currentDate();
        newRecord.setValue(ContributionTable::ValidFrom, QVariant(date.toString(Qt::ISODate)));
        model->insertRecord(-1, newRecord);
    } else {
        record.setValue(ContributionTable::Info, QVariant(anInfo));
        model->setRecord(0, record);
    }
    model->submitAll();
}

void ContributionModel::initTableView(QTableView *aTableView) const
{
    aTableView->setModel(model);

    aTableView->setColumnHidden(ContributionTable::ContributionId, true);
    aTableView->setColumnHidden(ContributionTable::MemberId, true);
    aTableView->setColumnHidden(ContributionTable::Debit, true);
}

}
}
