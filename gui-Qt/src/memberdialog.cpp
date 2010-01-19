#include <QtGui>

#include "memberdialog.h"

namespace GuiManagement {

MemberDialog::MemberDialog(ClubFrontend::Controller& aController, QWidget *parent) :
        QWidget(parent), controller(&aController)
{
    setupUi(this);

    const ClubFrontend::Member* member = controller->getMember();
    memberId->setText(QString::number(member->getId()));
    firstName->setText(QString::fromStdString(member->getFirstname()));
    memberName->setText(QString::fromStdString(member->getName()));
    nickname->setText(QString::fromStdString(member->getNickname()));
    city->setText(QString::fromStdString(member->getCity()));
    street->setText(QString::fromStdString(member->getStreet()));
    zipcode->setText(QString::number(member->getZipCode()));
    email->setText(QString::fromStdString(member->getEmail()));
    entryDate->setDate(
            QDate::fromString(
                    QString::fromStdString(member->getEntryDate()),
                    QString("dd.MM.yyyy")));
    info->setDocument(new QTextDocument(QString::fromStdString(member->getInfo())));

    const ClubFrontend::Contribution* contribution = controller->getContribution();
    contributionInfo->setText(QString::fromStdString(contribution->getInfo()));
    donation->setText(QString::number(contribution->getDonation()));
    fee->setText(QString::number(contribution->getFee()));

    const ClubFrontend::Bank* bank = controller->getBank();
    account->setText(QString::number(bank->getAccount()));
    code->setText(QString::number(bank->getCode()));
    bankName->setText(QString::fromStdString(bank->getName()));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(saveMember()));
}

void MemberDialog::setMemberId(const int& anId)
{
    QString id;
    id.setNum(anId);
    memberId->setText(id);
}

void MemberDialog::saveMember()
{
    ClubFrontend::Member* const member = controller->getMember();
    member->setName(memberName->text().toStdString());
    member->setFirstname(firstName->text().toStdString());
    member->setNickname(nickname->text().toStdString());
    member->setStreet(street->text().toStdString());
    member->setCity(city->text().toStdString());
    member->setZipCode(zipcode->text().toInt());
    member->setEmail(email->text().toStdString());
    member->setEntryDate(entryDate->text().toStdString());
    member->setInfo(info->toPlainText().toStdString());

    ClubFrontend::Bank* const bank = controller->getBank();
    bank->setAccount(account->text().toInt());
    bank->setCode(code->text().toInt());
    bank->setName(bankName->text().toStdString());

    ClubFrontend::Contribution* contribution = controller->getContribution();
    contribution->setDonation(donation->text().toInt());
    contribution->setFee(fee->text().toInt());
    contribution->setInfo(contributionInfo->text().toStdString());

    ClubFrontend::Resources* const resources = controller->getResources();
    resources->setEmailIntern(email->text().toStdString());

    controller->saveMember(member,bank,contribution,resources);
}

}
