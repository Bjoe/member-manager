#ifndef MEMBERDETAILVIEW_H
#define MEMBERDETAILVIEW_H

#include <QtCore>
#include <QtGui>
#include "ui_mainwindow.h"
#include "member.h"

namespace membermanager
{
namespace gui
{

class MemberDetailView : public QObject
{
    Q_OBJECT
public:
    explicit MemberDetailView(const Ui::MainWindow *anUi, QObject *aParent = 0);

    void showMember(Member aMember);

public slots:
    void saveMember();
    void newFee();

private:
    bool newContribution;
    Member member;
    const Ui::MainWindow *ui;
};

}
}

#endif // MEMBERDETAILVIEW_H
