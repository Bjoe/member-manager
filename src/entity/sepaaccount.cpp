#include "sepaaccount.h"

namespace membermanager {
namespace entity {

QString SepaAccount::iban() const
{
    return m_iban;
}

void SepaAccount::setIban(QString iban)
{
    m_iban = iban;
}

QString SepaAccount::bic() const
{
    return m_bic;
}

void SepaAccount::setBic(QString bic)
{
    m_bic = bic;
}

QDate SepaAccount::mandateDate() const
{
    return m_mandateDate;
}

void SepaAccount::setMandateDate(QDate date)
{
    m_mandateDate = date;
}

QString SepaAccount::memberId() const
{
    return m_memberId;
}

void SepaAccount::setMemberId(QString id)
{
    m_memberId = id;
}

QString SepaAccount::sequenceState() const
{
    return m_sequenceState;
}

void SepaAccount::setSequenceState(QString state)
{
    m_sequenceState = state;
}

} // namespace entity
} // namespace membermanager
