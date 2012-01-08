#include "member.h"

#include "model/databasestructure.h"
#include "model/memberdao.h"

namespace membermanager
{

Member::Member() :
    memberRecord(), addressRecord(), bankRecord(), ressourcenRecord()
{
}

Member::Member(const model::MemberFilter &aFilter) :
    memberRecord(), addressRecord(), bankRecord(), ressourcenRecord()
{
    model::MemberDao dao(QSqlDatabase::database());

    addressRecord = dao.getRecordWithMemberId(model::AddressTable::TABLENAME, aFilter);
    bankRecord = dao.getRecordWithMemberId(model::BankAccountTable::TABLENAME, aFilter);
    ressourcenRecord = dao.getRecordWithMemberId(model::RessourcenTable::TABLENAME, aFilter);
    memberRecord = dao.getRecordWithMemberId(model::MemberTable::TABLENAME, aFilter);
}

bool Member::save()
{
    model::MemberDao dao(QSqlDatabase::database());

    model::MemberFilter filter = model::MemberFilter::build().withMemberId(getMemberId());

    bool successful = true;
    successful &= dao.saveRecordWithMemberId(model::MemberTable::TABLENAME, filter, memberRecord);
    successful &= dao.saveRecordWithMemberId(model::RessourcenTable::TABLENAME, filter, ressourcenRecord);
    successful &= dao.saveRecordWithMemberId(model::BankAccountTable::TABLENAME, filter, bankRecord);
    successful &= dao.saveRecordWithMemberId(model::AddressTable::TABLENAME, filter, addressRecord);
    return successful;
}

MemberContribution Member::getMemberContribution() const
{
    model::MemberFilter filter = model::MemberFilter::build().withMemberId(getMemberId());
    MemberContribution memberContribution(filter);
    return memberContribution;
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

}
