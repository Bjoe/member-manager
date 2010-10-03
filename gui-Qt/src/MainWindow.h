#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QModelIndex>

#include "ui_mainWindow.h"
#include "MemberModel.h"
#include "KassaModel.h"
#include "MemberDetailModel.h"

namespace ClubFrontend
{

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
	MainWindow(MemberModel& aMemberModel, KassaModel& aKassaModel,
			QWidget* parent = 0);

private slots:
	void showDeletedMemberView();
	void showMemberView();
	void showKassaView();
	void newMember();
	void editMember(const QModelIndex& anIndex);

private:
	Ui::MainWindow ui;
	MemberModel& memberModel;
	KassaModel& kassaModel;

	void showDeletedMember(const bool aBoolean);
	void showMemberDialog(MemberDetailModel& aModel);
};

}

#endif // MAINWINDOW_H
