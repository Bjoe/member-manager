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
	void showSaldo();
	void newMember();
	void selectedMember();
	void editMember(const QModelIndex& anIndex);
	void copyMailAdress();

private:
	Ui::MainWindow ui;
	MemberModel& memberModel;
	KassaModel& kassaModel;

	void showMembers(const bool aBoolean);
	void showMemberDialog(MemberDetailModel& aModel);
	QModelIndex getSelection() const;
};

}

#endif // MAINWINDOW_H
