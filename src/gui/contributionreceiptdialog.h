#ifndef MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTDIALOG_H
#define MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTDIALOG_H

#include <QDialog>

#include "ui_contributionreceiptdialog.h"

namespace membermanager
{
namespace gui
{

class ContributionReceiptDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ContributionReceiptDialog(int aMemberId, QWidget *parent = 0);
    ~ContributionReceiptDialog();

private slots:
    void showContribution();

private:
    ::Ui::ContributionReceiptDialog ui;
    int memberId;
};


} // namespace gui
} // namespace membermanager
#endif // MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTDIALOG_H
