#include "bankaccount.h"

namespace membermanager {
namespace entity {

int BankAccount::bankAccountId() const
{
    return m_bankaccountId;
}

void BankAccount::setBankAccountId(int id)
{
    m_bankaccountId = id;
}

int BankAccount::memberId() const
{
    return m_memberId;
}

void BankAccount::setMemberId(int id)
{
    m_memberId = id;
}

QString BankAccount::name() const
{
    return m_name;
}

void BankAccount::setName(QString name)
{
    m_name = name;
}

QString BankAccount::accountNumber() const
{
    return m_accountNumber;
}

void BankAccount::setAccountNumber(QString number)
{
    m_accountNumber = number;
}

QString BankAccount::code() const
{
    return m_code;
}

void BankAccount::setCode(QString code)
{
    m_code = code;
}

} // namespace entity
} // namespace membermanager
