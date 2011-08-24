#ifndef CONTRIBUTIONDIALOG_H
#define CONTRIBUTIONDIALOG_H

#include <QtGui/QDialog>
#include "ui_contributiondialog.h"

#include "model/contributionmodel.h"

namespace ClubFrontend
{
namespace Gui
{
  
class ContributionDialog : public QDialog
{
    Q_OBJECT

public:
    ContributionDialog ( Model::ContributionModel *aContributionModel, QWidget* parent = 0 );
    ~ContributionDialog();

private:
    Ui::ContributionDialogClass ui;
    Model::ContributionModel *contributionModel;
};

}
}

#endif // CONTRIBUTIONDIALOG_H
