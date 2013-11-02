#include "cashaccount.h"

namespace membermanager {
namespace entity {

int CashAccount::cashAccountId() const
{
    return m_cashAccountId;
}

void CashAccount::setCashAccountId(int id)
{
    m_cashAccountId = id;
}

bool CashAccount::isDeleted() const
{
    return m_deleted;
}

void CashAccount::setDeleted(bool deleted)
{
    m_deleted = deleted;
}

QString CashAccount::primanota() const
{
    return m_primanota;
}

void CashAccount::setPrimanota(const QString &primanota)
{
    m_primanota = primanota;
}

QDate CashAccount::valuta() const
{
    return m_valuta;
}

void CashAccount::setValuta(const QDate &valuta)
{
    m_valuta = valuta;
}

QDate CashAccount::date() const
{
    return m_date;
}

void CashAccount::setDate(const QDate &date)
{
    m_date = date;
}

double CashAccount::value() const
{
    return m_value;
}

void CashAccount::setValue(double value)
{
    m_value = value;
}

int CashAccount::transactionCode() const
{
    return m_transactionCode;
}

void CashAccount::setTransactionCode(int code)
{
    m_transactionCode = code;
}

QString CashAccount::transactionText() const
{
    return m_transactionText;
}

void CashAccount::setTransactionText(const QString &text)
{
    m_transactionText = text;
}

QString CashAccount::remoteName() const
{
    return m_remoteName;
}

void CashAccount::setRemoteName(const QString &name)
{
    m_remoteName = name;
}

QString CashAccount::remoteBankCode() const
{
    return m_remoteBankCode;
}

void CashAccount::setRemoteBankCode(const QString &code)
{
    m_remoteBankCode = code;
}

QString CashAccount::remoteAccountNumber() const
{
    return m_remoteAccountNumber;
}

void CashAccount::setRemoteAccountNumber(const QString &number)
{
    m_remoteAccountNumber = number;
}

QString CashAccount::purpose() const
{
    return m_purpose;
}

void CashAccount::setPurpose(const QString &text)
{
    m_purpose = text;
}

QString CashAccount::memberId() const
{
    return m_memberId;
}

void CashAccount::setMemberId(QString id)
{
    m_memberId = id;
}

bool CashAccount::isBooked() const
{
    return m_booked;
}

void CashAccount::setBooked(bool booked)
{
    m_booked = booked;
}

} // namespace entity
} // namespace membermanager
