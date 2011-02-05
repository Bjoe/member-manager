#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QModelIndex>

#include "ui_MainWindow.h"
#include "Model/MemberModel.h"
#include "Model/KassaModel.h"
#include "Model/MemberDetailModel.h"

namespace ClubFrontend
{
namespace Gui
{

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow ( Model::MemberModel& aMemberModel, Model::KassaModel& aKassaModel,
                 QWidget* parent = 0 );

private slots:
    void showDeletedMemberView();
    void showMemberView();
    void showKassaView();
    void showSaldo();
    // TODO neue View showSaldoSum() einbauen
    void newMember();
    void selectedMember();
    void editMember ( const QModelIndex& anIndex );

private:
    Ui::MainWindow ui;
    Model::MemberModel& memberModel;
    Model::KassaModel& kassaModel;

    void showMembers ( const bool aBoolean );
    void showMemberDialog ( Model::MemberDetailModel& aModel );
    QModelIndex getSelection() const;
};

}
}

#endif // MAINWINDOW_H
