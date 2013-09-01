#include "member.h"

#include <QChar>

namespace membermanager {
namespace entity {

int Member::memberId() const
{
    return m_memberId;
}

void Member::setMemberId(int id)
{
    m_memberId = id;
}

QString Member::name() const
{
    return m_name;
}

void Member::setName(const QString &name)
{
    m_name = name;
}

QString Member::firstname() const
{
    return m_firstname;
}

void Member::setFirstname(const QString &name)
{
    m_firstname = name;
}

QString Member::nickname() const
{
    return m_nickname;
}

void Member::setNickname(const QString &name)
{
    m_nickname = name;
}

QString Member::email() const
{
    return m_email;
}

void Member::setEmail(const QString &email)
{
    m_email = email;
}

QDate Member::entryDate() const
{
    return m_entryDate;
}

void Member::setEntryDate(const QDate &date)
{
    m_entryDate = date;
}

QDate Member::cancellationDate() const
{
    return m_cancellationDate;
}

void Member::setCancellationDate(const QDate &date)
{
    m_cancellationDate = date;
}

QString Member::info() const
{
    return m_info;
}

void Member::setInfo(const QString &info)
{
    m_info = info;
}

QString Member::reference() const
{
    return m_reference;
}

void Member::setReference(const QString &reference)
{
    m_reference = reference;
}

QString Member::street() const
{
    return m_street;
}

void Member::setStreet(const QString &street)
{
    m_street = street;
}

QString Member::city() const
{
    return m_city;
}

void Member::setCity(const QString &city)
{
    m_city = city;
}

QString Member::zipCode() const
{
    return m_zipCode;
}

void Member::setZipCode(const QString &code)
{
    m_zipCode = code;
}

QString Member::collectionState() const
{
    return m_collectionState;
}

void Member::setCollectionState(QString state)
{
    m_collectionState = state;
}

void Member::setCollectionState(Member::CollectionState state)
{
    m_collectionState = QChar(static_cast<char>(state));
}

QString Member::accountNumber() const
{
    return m_accountNumber;
}

void Member::setAccountNumber(const QString &number)
{
    m_accountNumber = number;
}

QString Member::bankName() const
{
    return m_bankName;
}

void Member::setBankName(const QString &name)
{
    m_bankName = name;
}

QString Member::bankCode() const
{
    return m_bankCode;
}

void Member::setBankCode(const QString &code)
{
    m_bankCode = code;
}

QString Member::state() const
{
    return m_state;
}

void Member::setState(QString state)
{
    m_state = state;
}

void Member::setState(Member::State state)
{
    m_state = QChar(static_cast<char>(state));
}

} // namespace entity
} // namespace membermanager
