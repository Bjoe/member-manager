#include "contributionmodel.h"

#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

ContributionModel::ContributionModel(const MemberFilter &aFilter, const QSqlDatabase &aDb) :
    model(new QSqlTableModel(this, aDb))
{
    model->setObjectName(ContributionTable::TABLENAME);
    model->setTable(ContributionTable::TABLENAME);
    model->setHeaderData(ContributionTable::Fee, Qt::Horizontal, tr("Beitrag"));
    model->setHeaderData(ContributionTable::Donation, Qt::Horizontal, tr("Spende"));
    model->setHeaderData(ContributionTable::ValidFrom, Qt::Horizontal, tr("Gültig ab:"));
    model->setHeaderData(ContributionTable::Info, Qt::Horizontal, tr("Info"));

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

}
}
