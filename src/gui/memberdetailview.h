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

    void showMember(Member aMember);
    void saveMember();

public slots:
    void newFee();
    void showSaldoDialog();
    void showContributionDialog();

private:
    bool newContribution;
    Member member;
    accounting::ContributionEntry memberContribution;
    const Ui::MainWindow *ui;
};

}
}

#endif // MEMBERDETAILVIEW_H
