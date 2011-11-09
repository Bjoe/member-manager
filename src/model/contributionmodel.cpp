#include "contributionmodel.h"

#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

ContributionModel::ContributionModel(const MemberFilter &aFilter, const QSqlDatabase &aDb, QObject *aParent) :
    model(new QSqlTableModel(aParent, aDb))
{
    model->setObjectName(ContributionTable::TABLENAME);
    model->setTable(ContributionTable::TABLENAME);
    model->setHeaderData(ContributionTable::Fee, Qt::Horizontal, aParent->tr("Beitrag"));
    model->setHeaderData(ContributionTable::Donation, Qt::Horizontal, aParent->tr("Spende"));
    model->setHeaderData(ContributionTable::ValidFrom, Qt::Horizontal, aParent->tr("Gültig ab:"));
    model->setHeaderData(ContributionTable::Info, Qt::Horizontal, aParent->tr("Info"));

    model->setFilter(aFilter.createFilter());
    model->setSort(ContributionTable::ValidFrom, Qt::DescendingOrder);
    model->select();
}

ContributionModel::~ContributionModel()
{
}

void ContributionModel::initTableView(QTableView *aTableView) const
{
    aTableView->setModel(model);

    aTableView->setColumnHidden(ContributionTable::ContributionId, true);
    aTableView->setColumnHidden(ContributionTable::MemberId, true);
    aTableView->setColumnHidden(ContributionTable::Debit, true);
}

QString ContributionModel::getMemberId() const
{
    QSqlRecord record = model->record(0);
    QVariant id = record.value(ContributionTable::MemberId);
    return id.toString();
}

QModelIndex ContributionModel::insertNewRow()
{
    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row, ContributionTable::MemberId), getMemberId());
    model->submitAll();
    /// \todo model.lastError();
    return model->index(row, ContributionTable::Fee);
}

bool ContributionModel::deleteRow(const QModelIndex &anIndex)
{
    return model->removeRow(anIndex.row());
    /// \todo model.lastError();
}

}
}
