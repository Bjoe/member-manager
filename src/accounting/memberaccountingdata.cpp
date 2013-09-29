#include "memberaccountingdata.h"

#include "dao/bankaccounttablemodel.h"
#include "dao/contributiontablemodel.h"

#include "entity/bankaccount.h"
#include "entity/contribution.h"

namespace membermanager {
namespace accounting {

MemberAccountingData::MemberAccountingData(const entity::Member* member, const QDate& date)
    : m_date(date)
{
    m_memberId = QVariant(member->memberId());
    m_name = member->name();
    m_firstname = member->firstname();
    m_collectionState = member->collectionState();

    entity::BankAccount *bankaccount = dao::BankAccountTableModel::findByMemberId(m_memberId);
    m_bankAccountNumber = bankaccount->accountNumber();
    m_bankCode = bankaccount->code();

    entity::Contribution *contribution = dao::ContributionTableModel::findByMemberIdWithPointInTime(m_memberId, date);
    m_fee = contribution->fee();
    m_donation = contribution->donation();
    m_additionalFee = contribution->additionalFee();
    m_additionalDonation = contribution->additionalDonation();
    m_amortization = contribution->amortization();
}

QDate MemberAccountingData::date() const
{
    return m_date;
}

QVariant MemberAccountingData::memberId() const
{
    return m_memberId;
}

QString MemberAccountingData::name() const
{
    return m_name;
}

QString MemberAccountingData::firstname() const
{
    return m_firstname;
}

QString MemberAccountingData::bankAccountNumber() const
{
    return m_bankAccountNumber;
}

QString MemberAccountingData::bankCode() const
{
    return m_bankCode;
}

double MemberAccountingData::fee() const
{
    return m_fee;
}

double MemberAccountingData::donation() const
{
    return m_donation;
}

double MemberAccountingData::additionalFee() const
{
    return m_additionalFee;
}

double MemberAccountingData::additionalDonation() const
{
    return m_additionalDonation;
}

double MemberAccountingData::amortization() const
{
    return m_amortization;
}

bool MemberAccountingData::canCharge() const
{
    return ! m_collectionState.isEmpty() &&
            m_collectionState.at(0) == static_cast<char>(entity::Member::CollectionState::known) &&
           ! m_bankAccountNumber.isEmpty() &&
            ! m_bankCode.isEmpty();
}

} // namespace accounting
} // namespace membermanager
