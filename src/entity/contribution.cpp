#include "contribution.h"

namespace membermanager {
namespace entity {

int Contribution::contributionId() const
{
    return m_contributionId;
}

void Contribution::setContributionId(int id)
{
    m_contributionId = id;
    emit contributionIdChanged();
}

QString Contribution::memberId() const
{
    return m_memberId;
}

void Contribution::setMemberId(QString id)
{
    m_memberId = id;
    emit memberIdChanged();
}

double Contribution::fee() const
{
    return m_fee;
}

void Contribution::setFee(double fee)
{
    m_fee = fee;
    emit feeChanged();
}

double Contribution::additionalFee() const
{
    return m_additionalFee;
}

void Contribution::setAdditionalFee(double fee)
{
    m_additionalFee = fee;
    emit additionalFeeChanged();
}

double Contribution::additionalDonation() const
{
    return m_additionalDonation;
}

void Contribution::setAdditionalDonation(double donation)
{
    m_additionalDonation = donation;
    emit additionalDonationChanged();
}

double Contribution::donation() const
{
    return m_donation;
}

void Contribution::setDonation(double donation)
{
    m_donation = donation;
    emit donationChanged();
}

QString Contribution::info() const
{
    return m_info;
}

void Contribution::setInfo(const QString &text)
{
    m_info = text;
    emit infoChanged();
}

QDate Contribution::validFrom() const
{
    return m_validFrom;
}

void Contribution::setValidFrom(const QDate &date)
{
    m_validFrom = date;
    emit validFromChanged();
}

double Contribution::amortization() const
{
    return m_amortization;
}

void Contribution::setAmortization(double amortization)
{
    m_amortization = amortization;
    emit amortizationChanged();
}


} // namespace entity
} // namespace membermanager
