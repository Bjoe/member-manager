#include "member.h"

#include "model/databasestructure.h"
#include "model/memberdao.h"

namespace membermanager
{

Member::Member() :
    addressModel(new QSqlTableModel()),
    bankAccountModel(new QSqlTableModel()),
    ressourcenModel(new QSqlTableModel()),
    memberModel(new QSqlTableModel()),
    contributionModel(new model::ContributionModel(QSqlDatabase::database())),
    saldoModel(0),
    id(0)
{
}

Member::Member(int anId) :
    addressModel(new QSqlTableModel()),
    bankAccountModel(new QSqlTableModel()),
    ressourcenModel(new QSqlTableModel()),
    memberModel(new QSqlTableModel()),
    contributionModel(new model::ContributionModel(QSqlDatabase::database())),
    saldoModel(0),
    id(anId)
{
    initModels();
}

void Member::initModels()
{
    initTableModel(model::AddressTable::TABLENAME, addressModel);
    initTableModel(model::BankAccountTable::TABLENAME, bankAccountModel);
    initTableModel(model::RessourcenTable::TABLENAME, ressourcenModel);
    initTableModel(model::MemberTable::TABLENAME, memberModel);

    contributionModel->selectMemberId(id);
}

void Member::initTableModel(const QString &aTableName,
                            QSqlTableModel *const aModel)
{
    QString pkey = model::MemberTable::COLUMNNAME[model::MemberTable::MemberId];
    QString filter = QString(pkey + " = %1").arg(id);

    aModel->setTable(aTableName);
    aModel->setObjectName(aTableName);
    aModel->setFilter(filter);
    aModel->select();
}

QString Member::getValue(const QSqlTableModel *aModel, int aColumn) const
{
    const QSqlRecord record = aModel->record(0);
    const QVariant variant = record.value(aColumn);
    return variant.toString();
}

void Member::submitContribution(const QString &aFee, const QString &aDonation, const QString &anInfo)
{
    contributionModel->submit(aFee, aDonation, anInfo);
}

// \todo Refactor Inline ?
int Member::getMemberId() const
{
    return id;
}

QString Member::getFirstname() const
{
    return getValue(memberModel, model::MemberTable::FirstName);
}

QString Member::getName() const
{
    return getValue(memberModel, model::MemberTable::Name);
}

QString Member::getNickname() const
{
    return getValue(memberModel, model::MemberTable::NickName);
}

QString Member::getEmail() const
{
    return getValue(ressourcenModel, model::RessourcenTable::EmailAdress);
}

QString Member::getStreet() const
{
    return getValue(addressModel, model::AddressTable::Street);
}

QString Member::getTown() const
{
    return getValue(addressModel, model::AddressTable::Town);
}

QString Member::getZipCode() const
{
    return getValue(addressModel, model::AddressTable::ZipCode);
}

QString Member::getAccountNr() const
{
    return getValue(bankAccountModel, model::BankAccountTable::AccountNr);
}

QString Member::getBankName() const
{
    return getValue(bankAccountModel, model::BankAccountTable::BankName);
}

QString Member::getCode() const
{
    return getValue(bankAccountModel, model::BankAccountTable::Code);
}

QString Member::getDonation() const
{
    return contributionModel->getDonation();
}

float Member::getDonationAsFloat() const
{
    return contributionModel->getDonationValue().toFloat();
}

QString Member::getFee() const
{
    return contributionModel->getFee();
}

float Member::getFeeAsFloat() const
{
    return contributionModel->getFeeValue().toFloat();
}

QString Member::getContributionInfo() const
{
    return contributionModel->getInfo();
}

void Member::initAddressMapper(QDataWidgetMapper *aMapper) const
{
    aMapper->setModel(addressModel);
}

void Member::initBankAccountMapper(QDataWidgetMapper *aMapper) const
{
    aMapper->setModel(bankAccountModel);
}

void Member::initMemberMapper(QDataWidgetMapper *aMapper) const
{
    aMapper->setModel(memberModel);
}

void Member::initRessourcenMapper(QDataWidgetMapper *aMapper) const
{
    aMapper->setModel(ressourcenModel);
}

model::ContributionModel *Member::getContributionModel() const
{
    return contributionModel;
}

model::SaldoModel *Member::getSaldoModel() const
{
    return saldoModel;
}

}
