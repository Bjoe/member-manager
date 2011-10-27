#ifndef MEMBERMAPPER_H
#define MEMBERMAPPER_H

#include <QtGui>

#include "ui_mainwindow.h"
#include "member.h"

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

    void map(int anId);

public slots:
    void newMember();

private slots:
    void submitContribution();

private:
    void showMember();

    Member member;
    const Ui::MainWindow *ui;
    QDataWidgetMapper * const memberMapper;
    QDataWidgetMapper * const addressMapper;
    QDataWidgetMapper * const bankMapper;
    QDataWidgetMapper * const ressourcenMapper;
};

}
}

#endif // MEMBERMAPPER_H
