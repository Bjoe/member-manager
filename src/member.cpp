#include "member.h"

#include "dao/databasestructure.h"

namespace membermanager
{

Member::Member() :
    memberRecord(), addressRecord(), bankRecord(), resourceRecord()
{
}

int Member::getMemberId() const
{
    return memberRecord.value(dao::MemberTable::MemberId).toInt();
}

QString Member::getFirstname() const
{
    return memberRecord.value(dao::MemberTable::FirstName).toString();
}

void Member::setFirstname(const QString &aName)
{
    memberRecord.setValue(dao::MemberTable::FirstName, QVariant(aName));
}

QString Member::getName() const
{
    return memberRecord.value(dao::MemberTable::Name).toString();
}

void Member::setName(const QString &aName)
{
    memberRecord.setValue(dao::MemberTable::Name, QVariant(aName));
}

QString Member::getNickname() const
{
    return memberRecord.value(dao::MemberTable::NickName).toString();
}

void Member::setNickname(const QString &aName)
{
    memberRecord.setValue(dao::MemberTable::NickName, QVariant(aName));
}

bool Member::isCollection() const
{
    return memberRecord.value(dao::MemberTable::FOO_Einzug).toBool();
}

void Member::setCollection(bool aCollection)
{
    memberRecord.setValue(dao::MemberTable::FOO_Einzug, QVariant(aCollection));
}

QString Member::getEmail() const
{
    return resourceRecord.value(dao::RessourcenTable::EmailAdress).toString();
}

void Member::setEmail(const QString &anEmailAddress)
{
    resourceRecord.setValue(dao::RessourcenTable::EmailAdress, QVariant(anEmailAddress));
}

QDate Member::getEntryDate() const
{
    return memberRecord.value(dao::MemberTable::EntryDate).toDate();
}

void Member::setEntryDate(const QDate &aDate)
{
    memberRecord.setValue(dao::MemberTable::EntryDate, QVariant(aDate));
}

QString Member::getInfo() const
{
    return memberRecord.value(dao::MemberTable::Info).toString();
}

void Member::setInfo(const QString &anInfo)
{
    memberRecord.setValue(dao::MemberTable::Info, QVariant(anInfo));
}

QString Member::getReference() const
{
    return memberRecord.value(dao::MemberTable::FOO_ChaosNr).toString();
}

void Member::setReference(const QString &aReference)
{
    memberRecord.setValue(dao::MemberTable::FOO_ChaosNr, QVariant(aReference));
}

QString Member::getStreet() const
{
    return addressRecord.value(dao::AddressTable::Street).toString();
}

void Member::setStreet(const QString &aStreet)
{
    addressRecord.setValue(dao::AddressTable::Street, QVariant(aStreet));
}

QString Member::getCity() const
{
    return addressRecord.value(dao::AddressTable::Town).toString();
}

void Member::setCity(const QString &aCity)
{
    addressRecord.setValue(dao::AddressTable::Town, QVariant(aCity));
}

QString Member::getZipCode() const
{
    return addressRecord.value(dao::AddressTable::ZipCode).toString();
}

void Member::setZipCode(const QString &aCode)
{
    addressRecord.setValue(dao::AddressTable::ZipCode, QVariant(aCode));
}

/// \todo Refactor: Rename AccountNumber()
QString Member::getAccountNr() const
{
    return bankRecord.value(dao::BankAccountTable::AccountNr).toString();
}

void Member::setAccountNr(const QString &aNr)
{
    bankRecord.setValue(dao::BankAccountTable::AccountNr, QVariant(aNr));
}

QString Member::getBankName() const
{
    return bankRecord.value(dao::BankAccountTable::BankName).toString();
}

void Member::setBankName(const QString &aName)
{
    bankRecord.setValue(dao::BankAccountTable::BankName, QVariant(aName));
}

/// \todo Refactor: Rename BankCode()
QString Member::getCode() const
{
    return bankRecord.value(dao::BankAccountTable::Code).toString();
}

void Member::setCode(const QString &aCode)
{
    bankRecord.setValue(dao::BankAccountTable::Code, QVariant(aCode));
}

bool Member::isDeleted() const
{
   return memberRecord.value(dao::MemberTable::Deleted).toBool();
}

void Member::setDeleted(bool aDeleted)
{
    memberRecord.setValue(dao::MemberTable::Deleted, QVariant(aDeleted));
}

}
