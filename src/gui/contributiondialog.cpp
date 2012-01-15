#include "gui/contributiondialog.h"

#include <QModelIndex>
#include "model/databasestructure.h"

namespace membermanager
{
namespace gui
{

ContributionDialog::ContributionDialog(model::ContributionModel aContributionModel, QWidget *parent) :
    QDialog(parent), contributionModel(aContributionModel), ui()
{
    ui.setupUi(this);
    QString title = QString(tr("Member Id: %1")).arg(contributionModel.getMemberId());
    setWindowTitle(title);
    ui.contributionTableView->setModel(contributionModel.getModel());
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
    QModelIndex index = contributionModel.insertNewRow();
    ui.contributionTableView->setCurrentIndex(index);
    ui.contributionTableView->edit(index);
}

void ContributionDialog::deleteRow()
{
    QModelIndex index = ui.contributionTableView->currentIndex();
    contributionModel.deleteRow(index);
}

}
}
