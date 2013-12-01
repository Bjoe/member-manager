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
    emit cashAccountIdChanged();
}

QString CashAccount::primanota() const
{
    return m_primanota;
}

void CashAccount::setPrimanota(const QString &primanota)
{
    m_primanota = primanota;
    emit primanotaChanged();
}

QDate CashAccount::valuta() const
{
    return m_valuta;
}

void CashAccount::setValuta(const QDate &valuta)
{
    m_valuta = valuta;
    emit valutaChanged();
}

QDate CashAccount::date() const
{
    return m_date;
}

void CashAccount::setDate(const QDate &date)
{
    m_date = date;
    emit dateChanged();
}

double CashAccount::value() const
{
    return m_value;
}

void CashAccount::setValue(double value)
{
    m_value = value;
    emit valueChanged();
}

int CashAccount::transactionCode() const
{
    return m_transactionCode;
}

void CashAccount::setTransactionCode(int code)
{
    m_transactionCode = code;
    emit transactionCodeChanged();
}

QString CashAccount::transactionText() const
{
    return m_transactionText;
}

void CashAccount::setTransactionText(const QString &text)
{
    m_transactionText = text;
    emit transactionTextChanged();
}

QString CashAccount::remoteName() const
{
    return m_remoteName;
}

void CashAccount::setRemoteName(const QString &name)
{
    m_remoteName = name;
    emit remoteNameChanged();
}

QString CashAccount::remoteBankCode() const
{
    return m_remoteBankCode;
}

void CashAccount::setRemoteBankCode(const QString &code)
{
    m_remoteBankCode = code;
    emit remoteBankCodeChanged();
}

QString CashAccount::remoteAccountNumber() const
{
    return m_remoteAccountNumber;
}

void CashAccount::setRemoteAccountNumber(const QString &number)
{
    m_remoteAccountNumber = number;
    emit remoteAccountNumeberChanged();
}

QString CashAccount::purpose() const
{
    return m_purpose;
}

void CashAccount::setPurpose(const QString &text)
{
    m_purpose = text;
    emit purposeChanged();
}

QString CashAccount::memberId() const
{
    return m_memberId;
}

void CashAccount::setMemberId(QString id)
{
    m_memberId = id;
    emit memberIdChanged();
}

QString CashAccount::state() const
{
    return m_state;
}

void CashAccount::setState(QString state)
{
    m_state = state;
    emit stateChanged();
}

} // namespace entity
} // namespace membermanager
