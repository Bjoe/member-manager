#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QWidget>
#include <QSqlRecord>
#include "ui_memberDialog.h"
#include "MemberDetailModel.h"

namespace ClubFrontend
{

class MemberDialog : public QWidget, public Ui::MemberDialog
{
	Q_OBJECT

public:
	MemberDialog(QWidget *parent = 0);
	void showMember();
	void setMemberId(const int& anId);

private slots:
	void saveMember();

private:
	MemberDetailModel memberDetailModel;
};

}

#endif // MEMBERDIALOG_H
