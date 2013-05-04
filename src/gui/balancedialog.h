#ifndef MEMBERMANAGER_GUI_BALANCEDIALOG_H
#define MEMBERMANAGER_GUI_BALANCEDIALOG_H

#include <QDialog>

#include "ui_balancedialog.h"

#include "dao/balancedao.h"

namespace membermanager
{
namespace gui
{

class BalanceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BalanceDialog(int aMemberId, QWidget *parent = 0);

public slots:
    void copy();
    void insertRow();
    void deleteRow();
    void calculateSum();

private:
    dao::BalanceDao balanceDao;
    Ui::BalanceDialogClass ui;
    int memberId;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_BALANCEDIALOG_H
