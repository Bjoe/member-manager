#ifndef CONTRIBUTIONDIALOG_H
#define CONTRIBUTIONDIALOG_H

#include <QtGui/QDialog>
#include "ui_contributiondialog.h"

#include "model/contributionmodel.h"

namespace membermanager
{
namespace gui
{

class ContributionDialog : public QDialog
{
    Q_OBJECT

public:
    ContributionDialog(model::ContributionModel aContributionModel, QWidget *parent = 0);
    ~ContributionDialog();

private slots:
    void insertRow();
    void deleteRow();

private:
    Ui::ContributionDialogClass ui;
    model::ContributionModel contributionModel;
};

}
}

#endif // CONTRIBUTIONDIALOG_H
