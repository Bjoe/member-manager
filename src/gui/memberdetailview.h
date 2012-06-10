#ifndef MEMBERDETAILVIEW_H
#define MEMBERDETAILVIEW_H

#include <QtCore>
#include <QtGui>
#include "ui_memberdetailview.h"
#include "member.h"
#include "dao/memberdao.h"
#include "accounting/contributionentry.h"

namespace membermanager
{
namespace gui
{

class MemberDetailView : public QWidget
{
    Q_OBJECT
public:
    explicit MemberDetailView(bool isDeleted, QWidget *aParent = 0);

    void showMember(int aMemberId);

public slots:
    void updateMemberDetailView(const QItemSelection &aSelected, const QItemSelection &aDeselected);
    void newMember();
    void saveMember();
    void newFee();
    void showSaldoDialog();
    void showContributionDialog();
    void showContributionReceiptDialog();

private:
    Ui::MemberDetailView ui;

    dao::MemberDao memberDao;
    Member member;
    accounting::ContributionEntry memberContribution;
    bool newContribution;
};

}
}

#endif // MEMBERDETAILVIEW_H
