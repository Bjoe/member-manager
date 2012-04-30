#ifndef MEMBERDETAILVIEW_H
#define MEMBERDETAILVIEW_H

#include <QtCore>
#include <QtGui>
#include "ui_mainwindow.h"
#include "member.h"
#include "accounting/contributionentry.h"

namespace membermanager
{
namespace gui
{

class MemberDetailView : public QWidget
{
    Q_OBJECT
public:
    explicit MemberDetailView(const Ui::MainWindow *anUi, QWidget *aParent = 0);

    void showMember(int aMemberId);
    void saveMember();

public slots:
    void newFee();
    void showSaldoDialog();
    void showContributionDialog();

private:
    const Ui::MainWindow *ui;
    Member member;
    accounting::ContributionEntry memberContribution;
    bool newContribution;
};

}
}

#endif // MEMBERDETAILVIEW_H
