#include "gui/contributiondialog.h"

namespace membermanager
{
namespace gui
{

ContributionDialog::ContributionDialog(model::ContributionModel *aContributionModel, QWidget *parent) :
    QDialog(parent), contributionModel(aContributionModel), ui()
{
    ui.setupUi(this);
    contributionModel->initTableView(ui.contributionTableView);

    ui.contributionTableView->resizeColumnsToContents();
}

ContributionDialog::~ContributionDialog()
{

}

}
}
