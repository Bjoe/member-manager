#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "ui_memberDialog.h"
#include "MemberDetailModel.h"

namespace ClubFrontend
{

class MemberDialog : public QWidget
{
	Q_OBJECT

public:
	MemberDialog(const int anId, QWidget *parent = 0);

private:
	MemberDetailModel memberDetailModel;
	QDataWidgetMapper* memberMapper;
	QDataWidgetMapper* addressMapper;
	QDataWidgetMapper* bankMapper;
	QDataWidgetMapper* contributionMapper;
	QDataWidgetMapper* ressourcenMapper;

	Ui::MemberDialog ui;
};

}

#endif // MEMBERDIALOG_H
