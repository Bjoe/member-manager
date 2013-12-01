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
    emit ibanChanged();
}

QString SepaAccount::bic() const
{
    return m_bic;
}

void SepaAccount::setBic(QString bic)
{
    m_bic = bic;
    emit bicChanged();
}

QDate SepaAccount::mandateDate() const
{
    return m_mandateDate;
}

void SepaAccount::setMandateDate(QDate date)
{
    m_mandateDate = date;
    emit mandateDateChanged();
}

QString SepaAccount::memberId() const
{
    return m_memberId;
}

void SepaAccount::setMemberId(QString id)
{
    m_memberId = id;
    emit memberIdChanged();
}

QString SepaAccount::sequenceState() const
{
    return m_sequenceState;
}

void SepaAccount::setSequenceState(QString state)
{
    m_sequenceState = state;
    emit sequenceStateChanged();
}

} // namespace entity
} // namespace membermanager
