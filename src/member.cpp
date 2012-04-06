#include "member.h"

#include "model/databasestructure.h"
#include "model/memberdao.h"

namespace membermanager
{

Member::Member() :
    memberRecord(), addressRecord(), bankRecord(), ressourcenRecord()
{
}

Member::Member(int aMemberId) :
    memberRecord(), addressRecord(), bankRecord(), ressourcenRecord()
{
    model::MemberDao dao(QSqlDatabase::database());

    addressRecord = dao.getRecordWithMemberId(model::AddressTable::TABLENAME, aMemberId);
    bankRecord = dao.getRecordWithMemberId(model::BankAccountTable::TABLENAME, aMemberId);
    ressourcenRecord = dao.getRecordWithMemberId(model::RessourcenTable::TABLENAME, aMemberId);
    memberRecord = dao.getRecordWithMemberId(model::MemberTable::TABLENAME, aMemberId);
}

bool Member::save()
{
    model::MemberDao dao(QSqlDatabase::database());

    int memberId = getMemberId();
    bool successful = true;
    successful &= dao.saveRecordWithMemberId(model::MemberTable::TABLENAME, memberId, memberRecord);
    successful &= dao.saveRecordWithMemberId(model::RessourcenTable::TABLENAME, memberId, ressourcenRecord);
    successful &= dao.saveRecordWithMemberId(model::BankAccountTable::TABLENAME, memberId, bankRecord);
    successful &= dao.saveRecordWithMemberId(model::AddressTable::TABLENAME, memberId, addressRecord);
    return successful;
}

model::SaldoModel Member::getSaldoModel()
{
    model::SaldoModel saldoModel(getMemberId(), QSqlDatabase::database());
    return saldoModel;
}

model::ContributionModel Member::getContributionModel()
{
    model::ContributionModel contributionModel(getMemberId(), QSqlDatabase::database());
    return contributionModel;
}

int Member::getMemberId() const
{
    return memberRecord.value(model::MemberTable::MemberId).toInt();
}

QString Member::getFirstname() const
{
    return memberRecord.value(model::MemberTable::FirstName).toString();
}

void Member::setFirstname(const QString &aName)
{
    memberRecord.setValue(model::MemberTable::FirstName, QVariant(aName));
}

QString Member::getName() const
{
    return memberRecord.value(model::MemberTable::Name).toString();
}

void Member::setName(const QString &aName)
{
    memberRecord.setValue(model::MemberTable::Name, QVariant(aName));
}

QString Member::getNickname() const
{
    return memberRecord.value(model::MemberTable::NickName).toString();
}

void Member::setNickname(const QString &aName)
{
    memberRecord.setValue(model::MemberTable::NickName, QVariant(aName));
}

bool Member::isCollection() const
{
    return memberRecord.value(model::MemberTable::FOO_Einzug).toBool();
}

void Member::setCollection(bool aCollection)
{
    memberRecord.setValue(model::MemberTable::FOO_Einzug, QVariant(aCollection));
}

QString Member::getEmail() const
{
    return ressourcenRecord.value(model::RessourcenTable::EmailAdress).toString();
}

void Member::setEmail(const QString &anEmailAddress)
{
    ressourcenRecord.setValue(model::RessourcenTable::EmailAdress, QVariant(anEmailAddress));
}

QDate Member::getEntryDate() const
{
    return memberRecord.value(model::MemberTable::EntryDate).toDate();
}

void Member::setEntryDate(const QDate &aDate)
{
    memberRecord.setValue(model::MemberTable::EntryDate, QVariant(aDate));
}

QString Member::getInfo() const
{
    return memberRecord.value(model::MemberTable::Info).toString();
}

void Member::setInfo(const QString &anInfo)
{
    memberRecord.setValue(model::MemberTable::Info, QVariant(anInfo));
}

QString Member::getReference() const
{
    return memberRecord.value(model::MemberTable::FOO_ChaosNr).toString();
}

void Member::setReference(const QString &aReference)
{
    memberRecord.setValue(model::MemberTable::FOO_ChaosNr, QVariant(aReference));
}

QString Member::getStreet() const
{
    return addressRecord.value(model::AddressTable::Street).toString();
}

void Member::setStreet(const QString &aStreet)
{
    addressRecord.setValue(model::AddressTable::Street, QVariant(aStreet));
}

QString Member::getCity() const
{
    return addressRecord.value(model::AddressTable::Town).toString();
}

void Member::setCity(const QString &aCity)
{
    addressRecord.setValue(model::AddressTable::Town, QVariant(aCity));
}

QString Member::getZipCode() const
{
    return addressRecord.value(model::AddressTable::ZipCode).toString();
}

void Member::setZipCode(const QString &aCode)
{
    addressRecord.setValue(model::AddressTable::ZipCode, QVariant(aCode));
}

QString Member::getAccountNr() const
{
    return bankRecord.value(model::BankAccountTable::AccountNr).toString();
}

void Member::setAccountNr(const QString &aNr)
{
    bankRecord.setValue(model::BankAccountTable::AccountNr, QVariant(aNr));
}

QString Member::getBankName() const
{
    return bankRecord.value(model::BankAccountTable::BankName).toString();
}

void Member::setBankName(const QString &aName)
{
    bankRecord.setValue(model::BankAccountTable::BankName, QVariant(aName));
}

QString Member::getCode() const
{
    return bankRecord.value(model::BankAccountTable::Code).toString();
}

void Member::setCode(const QString &aCode)
{
    bankRecord.setValue(model::BankAccountTable::Code, QVariant(aCode));
}

bool Member::isDeleted() const
{
   return memberRecord.value(model::MemberTable::Deleted).toBool();
}

void Member::setDeleted(bool aDeleted)
{
    memberRecord.setValue(model::MemberTable::Deleted, QVariant(aDeleted));
}

}
