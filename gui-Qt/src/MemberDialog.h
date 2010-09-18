#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "ui_memberDialog.h"
#include "MemberDetailModel.h"

namespace ClubFrontend
{

class MemberDialog: public QWidget
{
Q_OBJECT

public:
	MemberDialog(const int anId, QWidget* parent = 0);
	virtual ~MemberDialog();

private:
	MemberDetailModel memberDetailModel;
	QDataWidgetMapper* const memberMapper;
	QDataWidgetMapper* const addressMapper;
	QDataWidgetMapper* const bankMapper;
	QDataWidgetMapper* const contributionMapper;
	QDataWidgetMapper* const ressourcenMapper;

	Ui::MemberDialog ui;
};

}

#endif // MEMBERDIALOG_H
