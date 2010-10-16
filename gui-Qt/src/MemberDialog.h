#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "ui_memberDialog.h"
#include "MemberDetailModel.h"

namespace ClubFrontend
{

class MemberDialog: public QDialog
{
Q_OBJECT

public:
	MemberDialog(MemberDetailModel& aMemberDetailModel, QWidget* parent = 0);
	virtual ~MemberDialog();

private slots:
	void deleteMember();
	void showSaldo();

private:
	MemberDetailModel& memberDetailModel;
	QDataWidgetMapper* const memberMapper;
	QDataWidgetMapper* const addressMapper;
	QDataWidgetMapper* const bankMapper;
	QDataWidgetMapper* const contributionMapper;
	QDataWidgetMapper* const ressourcenMapper;

	Ui::MemberDialog ui;
};

}

#endif // MEMBERDIALOG_H
