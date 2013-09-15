#include "memberdebt.h"

namespace membermanager {
namespace accounting {

MemberDebt::MemberDebt(QObject *parent) : QObject(parent),
    m_memberId(""), m_email(""), m_firstname(""), m_name(""), m_debit(0)
{
}

QString MemberDebt::memberId() const
{
    return m_memberId;
}

void MemberDebt::setMemberId(const QString &memberId)
{
    m_memberId = memberId;
    emit memberIdChanged();
}
QString MemberDebt::email() const
{
    return m_email;
}

void MemberDebt::setEmail(const QString &email)
{
    m_email = email;
    emit emailChanged();
}
QString MemberDebt::firstname() const
{
    return m_firstname;
}

void MemberDebt::setFirstname(const QString &firstname)
{
    m_firstname = firstname;
    emit firstnameChanged();
}
QString MemberDebt::name() const
{
    return m_name;
}

void MemberDebt::setName(const QString &name)
{
    m_name = name;
    emit nameChanged();
}
double MemberDebt::debit() const
{
    return m_debit;
}

void MemberDebt::setDebit(double debit)
{
    m_debit = debit;
    emit debitChanged();
}




} // namespace accounting
} // namespace membermanager
