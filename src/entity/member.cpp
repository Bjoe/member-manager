#include "member.h"

#include <QChar>

namespace membermanager {
namespace entity {

QString Member::memberId() const
{
    return m_memberId;
}

void Member::setMemberId(QString id)
{
    m_memberId = id;
    emit memberIdChanged();
}

QString Member::name() const
{
    return m_name;
}

void Member::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}

QString Member::firstname() const
{
    return m_firstname;
}

void Member::setFirstname(const QString &name)
{
    m_firstname = name;
    emit firstnameChanged();
}

QString Member::nickname() const
{
    return m_nickname;
}

void Member::setNickname(const QString &name)
{
    m_nickname = name;
    emit nicknameChanged();
}

QString Member::email() const
{
    return m_email;
}

void Member::setEmail(const QString &email)
{
    m_email = email;
    emit emailChanged();
}

QDate Member::entryDate() const
{
    return m_entryDate;
}

void Member::setEntryDate(const QDate &date)
{
    m_entryDate = date;
    emit entryDateChanged();
}

QDate Member::cancellationDate() const
{
    return m_cancellationDate;
}

void Member::setCancellationDate(const QDate &date)
{
    m_cancellationDate = date;
    emit cancellationDateChanged();
}

QString Member::info() const
{
    return m_info;
}

void Member::setInfo(const QString &info)
{
    m_info = info;
    emit infoChanged();
}

QString Member::reference() const
{
    return m_reference;
}

void Member::setReference(const QString &reference)
{
    m_reference = reference;
    emit referenceChanged();
}

QString Member::street() const
{
    return m_street;
}

void Member::setStreet(const QString &street)
{
    m_street = street;
    emit streetChanged();
}

QString Member::city() const
{
    return m_city;
}

void Member::setCity(const QString &city)
{
    m_city = city;
    emit cityChanged();
}

QString Member::zipCode() const
{
    return m_zipCode;
}

void Member::setZipCode(const QString &code)
{
    m_zipCode = code;
    emit zipCodeChanged();
}

QString Member::collectionState() const
{
    return m_collectionState;
}

void Member::setCollectionState(QString state)
{
    m_collectionState = state;
    emit collectionStateChanged();
}

void Member::setCollectionState(Member::CollectionState state)
{
    m_collectionState = QChar(static_cast<char>(state));
    emit collectionStateChanged();
}

QString Member::state() const
{
    return m_state;
}

void Member::setState(QString state)
{
    m_state = state;
    emit stateChanged();
}

void Member::setState(Member::State state)
{
    m_state = QChar(static_cast<char>(state));
    emit stateChanged();
}

} // namespace entity
} // namespace membermanager
