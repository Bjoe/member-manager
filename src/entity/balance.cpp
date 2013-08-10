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
}

int Balance::memberId() const
{
    return m_memberId;
}

void Balance::setMemberId(int id)
{
    m_memberId = id;
}

double Balance::value() const
{
    return m_value;
}

void Balance::setValue(double value)
{
    m_value = value;
}

QDate Balance::valuta() const
{
    return m_valuta;
}

void Balance::setValuta(const QDate &date)
{
    m_valuta = date;
}

QString Balance::purpose() const
{
    return m_purpose;
}

void Balance::setPurpose(const QString &purpose)
{
    m_purpose = purpose;
}

int Balance::account() const
{
    return m_account;
}

void Balance::setAccount(int account)
{
    m_account = account;
}

int Balance::cashAccountId() const
{
    return m_cashAccountId;
}

void Balance::setCashAccountId(int id)
{
    m_cashAccountId = id;
}

QString Balance::info() const
{
    return m_info;
}

void Balance::setInfo(const QString &info)
{
    m_info = info;
}

} // namespace entity
} // namespace membermanager
