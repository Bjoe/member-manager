#include <QtGui>

#include "MemberDialog.h"
#include "DatabaseStructure.h"
#include "SaldoDialog.h"
#include "SaldoModel.h"
#include "ContributionDialog.h"
#include "ContributionModel.h"

namespace ClubFrontend
{

MemberDialog::MemberDialog(MemberDetailModel& aMemberDetailModel,
		QWidget* parent) :
	QDialog(parent), memberDetailModel(aMemberDetailModel), memberMapper(
			new QDataWidgetMapper(this)), addressMapper(new QDataWidgetMapper(
			this)), bankMapper(new QDataWidgetMapper(this)),
			ressourcenMapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);

	QString id;
	id.setNum(memberDetailModel.getMemberId());
	ui.memberId->setText(id);

	memberMapper->setModel(memberDetailModel.getMemberTableModel());
	memberMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	memberMapper->addMapping(ui.firstName, MemberTable::FirstName);
	memberMapper->addMapping(ui.memberName, MemberTable::Name);
	memberMapper->addMapping(ui.nickname, MemberTable::NickName);
	memberMapper->addMapping(ui.entryDate, MemberTable::EntryDate);
	memberMapper->addMapping(ui.info, MemberTable::Info);
	memberMapper->toFirst();

	addressMapper->setModel(memberDetailModel.getAddressTableModel());
	addressMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	addressMapper->addMapping(ui.city, AddressTable::Town);

	addressMapper->addMapping(ui.street, AddressTable::Street);
	addressMapper->addMapping(ui.zipcode, AddressTable::ZipCode);
	addressMapper->toFirst();

	bankMapper->setModel(memberDetailModel.getBankAccountTableModel());
	bankMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	bankMapper->addMapping(ui.account, BankAccountTable::AccountNr);
	bankMapper->addMapping(ui.code, BankAccountTable::Code);
	bankMapper->addMapping(ui.bankName, BankAccountTable::BankName);
	bankMapper->toFirst();

	ContributionModel* model = memberDetailModel.getContributionModel();
	ui.contributionInfo->setText(model->getInfo());
	ui.donation->setText(model->getDonation());
	ui.fee->setText(model->getFee());;
	
	ressourcenMapper->setModel(memberDetailModel.getRessourcenTableModel());
	ressourcenMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	ressourcenMapper->addMapping(ui.email, RessourcenTable::EmailAdress);
	ressourcenMapper->toFirst();

	connect(ui.buttonBox, SIGNAL(accepted()), memberMapper, SLOT(submit()));
	connect(ui.buttonBox, SIGNAL(accepted()), addressMapper, SLOT(submit()));
	connect(ui.buttonBox, SIGNAL(accepted()), bankMapper, SLOT(submit()));
	connect(ui.buttonBox, SIGNAL(accepted()), SLOT(submitContribution()));
	connect(ui.buttonBox, SIGNAL(accepted()), ressourcenMapper, SLOT(submit()));

	QPushButton* discardButton =
			ui.buttonBox->button(QDialogButtonBox::Discard);
	connect(discardButton, SIGNAL(clicked()), this, SLOT(deleteMember()));

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(close()));

	connect(ui.saldoButton, SIGNAL(clicked()), this, SLOT(showSaldo()));
	connect(ui.feeButton, SIGNAL(clicked()), this, SLOT(showFee()));
}

MemberDialog::~MemberDialog()
{
	delete ressourcenMapper;
	delete bankMapper;
	delete addressMapper;
	delete memberMapper;
}

void MemberDialog::deleteMember()
{
	int exitStatus = QMessageBox::warning(this, tr("Loesche Mitglied"), tr(
			"Wollen Sie wirklich Mitglied mit der Nr. %1 loeschen?"). arg(
			memberDetailModel.getMemberId()), QMessageBox::Yes | QMessageBox::No);
	if (exitStatus == QMessageBox::Yes)
	{
		memberDetailModel.deleteMember();
	}
}

void MemberDialog::showSaldo()
{
  SaldoModel model(QSqlDatabase::database(), memberDetailModel.getMemberId());
  SaldoDialog dialog(model, this);

  dialog.exec();
}

void MemberDialog::showFee()
{
  ContributionModel* model = memberDetailModel.getContributionModel();
  ContributionDialog dialog(model, this);

  dialog.exec();
}

void MemberDialog::submitContribution()
{
  ContributionModel* model = memberDetailModel.getContributionModel();
  model->submit(ui.fee->text(), ui.donation->text(), ui.contributionInfo->text());
}

}
