#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QWidget>
#include "ui_memberDialog.h"

namespace ClubFrontend
{

class MemberDialog : public QWidget, public Ui::MemberDialog
{
	Q_OBJECT

public:
	MemberDialog(QWidget *parent = 0);
	void showMember() const;
	void setMemberId(const int& anId);

private slots:
	void saveMember();
};

}

#endif // MEMBERDIALOG_H
