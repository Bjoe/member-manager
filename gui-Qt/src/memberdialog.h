#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QWidget>
#include "ui_memberDialog.h"
#include "member.h"
#include "bank.h"
#include "contribution.h"
#include "controller.h"

namespace GuiManagement
{

class MemberDialog : public QWidget, public Ui::MemberDialog
{
	Q_OBJECT

public:
	MemberDialog(ClubFrontend::Controller& aController, QWidget *parent = 0);
	void showMember() const;
	void setMemberId(const int& anId);

private:
	ClubFrontend::Controller* controller;

private slots:
	void saveMember();
};

}

#endif // MEMBERDIALOG_H
