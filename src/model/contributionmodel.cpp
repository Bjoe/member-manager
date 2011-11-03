#include "contributionmodel.h"

#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

ContributionModel::ContributionModel(const QSqlDatabase &aDb) :
    model(new QSqlTableModel(this, aDb))
{
    model->setObjectName(ContributionTable::TABLENAME);
    model->setTable(ContributionTable::TABLENAME);
    model->setHeaderData(ContributionTable::Fee, Qt::Horizontal, tr("Beitrag"));
    model->setHeaderData(ContributionTable::Donation, Qt::Horizontal, tr("Spende"));
    model->setHeaderData(ContributionTable::ValidFrom, Qt::Horizontal, tr("Gültig ab:"));
    model->setHeaderData(ContributionTable::Info, Qt::Horizontal, tr("Info"));
}

ContributionModel::~ContributionModel()
{
}

void ContributionModel::selectMemberId(const int aMemberId)
{
    QString columname = ContributionTable::COLUMNNAME[ContributionTable::MemberId];
    QString filter = QString(columname + " = %1").arg(aMemberId);
    model->setFilter(filter);
    model->setSort(ContributionTable::ValidFrom, Qt::DescendingOrder);
    model->select();
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
