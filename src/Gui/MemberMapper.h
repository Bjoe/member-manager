#ifndef MEMBERMAPPER_H
#define MEMBERMAPPER_H

#include <QtGui>

#include "ui_MainWindow.h"
#include "Member.h"

namespace ClubFrontend
{
namespace Gui
{

class MemberMapper : public QObject
{
    Q_OBJECT
public:
    explicit MemberMapper(const Ui::MainWindow *anUi, QObject *parent = 0);
    void initUi();

    void newMember();
    void map(int anId);

private slots:
    void submitContribution();

private:
    void showMember();

    Member member;
    const Ui::MainWindow *ui;
    QDataWidgetMapper* const memberMapper;
    QDataWidgetMapper* const addressMapper;
    QDataWidgetMapper* const bankMapper;
    QDataWidgetMapper* const ressourcenMapper;
};

}
}

#endif // MEMBERMAPPER_H
