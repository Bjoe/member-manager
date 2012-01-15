#include "contributionmodel.h"

#include "model/databasestructure.h"
#include "model/memberfilter.h"

namespace membermanager
{
namespace model
{

ContributionModel::ContributionModel(int aMemberId, const QSqlDatabase &aDb, QObject *aParent) :
    memberId(aMemberId), model(new QSqlTableModel(aParent, aDb))
{
    model->setObjectName(ContributionTable::TABLENAME);
    model->setTable(ContributionTable::TABLENAME);
    model->setHeaderData(ContributionTable::Fee, Qt::Horizontal, aParent->tr("Beitrag"));
    model->setHeaderData(ContributionTable::Donation, Qt::Horizontal, aParent->tr("Spende"));
    model->removeColumn(ContributionTable::Debit);
    model->setHeaderData(ContributionTable::ValidFrom -1, Qt::Horizontal, aParent->tr("Gueltig ab"));
    model->setHeaderData(ContributionTable::Info -1, Qt::Horizontal, aParent->tr("Info"));

    MemberFilter filter = MemberFilter::build().withMemberId(memberId);
    model->setFilter(filter.createFilter());
    model->setSort(ContributionTable::ValidFrom -1, Qt::DescendingOrder);
    model->select();
}

ContributionModel::~ContributionModel()
{
}

QSqlTableModel *ContributionModel::getModel()
{
    return model;
}

int ContributionModel::getMemberId() const
{
    return memberId;
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
