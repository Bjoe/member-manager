#ifndef MEMBERMAPPER_H
#define MEMBERMAPPER_H

#include <QtGui>

#include "ui_mainwindow.h"
#include "member.h"

namespace membermanager
{
namespace gui
{

class MemberMapper : public QObject
{
    Q_OBJECT
public:
    explicit MemberMapper(const Ui::MainWindow *anUi, QObject *parent = 0);
    void initUi();

    void showMember(Member aMember);

private slots:
    void submitContribution();

private:
    Member member;
    const Ui::MainWindow *ui;
    QDataWidgetMapper *const memberMapper;
    QDataWidgetMapper *const addressMapper;
    QDataWidgetMapper *const bankMapper;
    QDataWidgetMapper *const ressourcenMapper;
};

}
}

#endif // MEMBERMAPPER_H
