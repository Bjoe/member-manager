#ifndef CONTRIBUTIONDIALOG_H
#define CONTRIBUTIONDIALOG_H

#include <QDialog>
#include "ui_contributiondialog.h"

#include "dao/contributiondao.h"

namespace membermanager
{
namespace gui
{

class ContributionDialog : public QDialog
{
    Q_OBJECT

public:
    ContributionDialog(int aMemberId, QWidget *parent = 0);
    ~ContributionDialog();

private slots:
    void insertRow();
    void deleteRow();

private:
    ::Ui::ContributionDialogClass ui;
    int memberId;
    dao::ContributionDao contributionDao;
};

}
}

#endif // CONTRIBUTIONDIALOG_H
