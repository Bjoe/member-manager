#include "gui/contributiondialog.h"

namespace ClubFrontend
{
namespace Gui
{
  
ContributionDialog::ContributionDialog ( Model::ContributionModel* aContributionModel, QWidget* parent ) :
        QDialog ( parent ), contributionModel ( aContributionModel ), ui()
{
    ui.setupUi ( this );
    contributionModel->initTableView( ui.contributionTableView );

    ui.contributionTableView->resizeColumnsToContents();
}

ContributionDialog::~ContributionDialog()
{

}

}
}
