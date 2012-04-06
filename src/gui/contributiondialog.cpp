#include "gui/contributiondialog.h"

#include <QModelIndex>
#include "model/databasestructure.h"

namespace membermanager
{
namespace gui
{

ContributionDialog::ContributionDialog(int aMemberId, QWidget *parent) :
    QDialog(parent), memberId(aMemberId), contributionDao(), ui()
{
    ui.setupUi(this);
    QString title = QString(tr("Member Id: %1")).arg(memberId);
    setWindowTitle(title);

    QSqlTableModel *model = contributionDao.getModelByMemberId(memberId);
    ui.contributionTableView->setModel(model);

    ui.contributionTableView->hideColumn(model::ContributionTable::ContributionId);
    ui.contributionTableView->hideColumn(model::ContributionTable::MemberId);
    ui.contributionTableView->sortByColumn(model::ContributionTable::ValidFrom -1, Qt::DescendingOrder);

    ui.contributionTableView->resizeColumnsToContents();

    connect(ui.newRowButton, SIGNAL(clicked()), SLOT(insertRow()));
    connect(ui.deleteRowButton, SIGNAL(clicked()), SLOT(deleteRow()));
}

ContributionDialog::~ContributionDialog()
{

}

void ContributionDialog::insertRow()
{
    QModelIndex index = contributionDao.insertNewEmptyRowWithMemberId(memberId);
    ui.contributionTableView->setCurrentIndex(index);
    ui.contributionTableView->edit(index);
}

void ContributionDialog::deleteRow()
{
    QModelIndex index = ui.contributionTableView->currentIndex();
    contributionDao.deleteRow(index);
}

}
}
