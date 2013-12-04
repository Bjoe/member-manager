#include "balance.h"

namespace membermanager {
namespace entity {

int Balance::balanceId() const
{
    return m_balanceId;
}

void Balance::setBalanceId(int id)
{
    m_balanceId = id;
    emit balanceIdChanged();
}

QString Balance::memberId() const
{
    return m_memberId;
}

void Balance::setMemberId(QString id)
{
    m_memberId = id;
    emit memberIdChanged();
}

double Balance::value() const
{
    return m_value;
}

void Balance::setValue(double value)
{
    m_value = value;
    emit valueChanged();
}

QDate Balance::valuta() const
{
    return m_valuta;
}

void Balance::setValuta(QDate date)
{
    m_valuta = date;
    emit valutaChanged();
}

QString Balance::accountingReference() const
{
    return m_accountingReference;
}

void Balance::setAccountingReference(QString reference)
{
    m_accountingReference = reference;
    emit accountingReferenceChanged();
}

QString Balance::purpose() const
{
    return m_purpose;
}

void Balance::setPurpose(QString purpose)
{
    m_purpose = purpose;
    emit purposeChanged();
}

int Balance::account() const
{
    return m_account;
}

void Balance::setAccount(int account)
{
    m_account = account;
    emit accountChanged();
}

int Balance::cashAccountId() const
{
    return m_cashAccountId;
}

void Balance::setCashAccountId(int id)
{
    m_cashAccountId = id;
    emit cashAccountIdChanged();
}

QString Balance::info() const
{
    return m_info;
}

void Balance::setInfo(QString info)
{
    m_info = info;
    emit infoChanged();
}

} // namespace entity
} // namespace membermanager
