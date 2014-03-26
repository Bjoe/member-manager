#include "memberaccountingdata.h"

#include "entity/member.h"

namespace membermanager {
namespace accounting {

MemberAccountingData::MemberAccountingData(QObject *parent) : QObject(parent)
{
}

QDate MemberAccountingData::valuta() const
{
    return m_valuta;
}

void MemberAccountingData::setValuta(QDate date)
{
    m_valuta = date;
    emit valutaChanged();
}

QString MemberAccountingData::mandateId() const
{
    return m_mandateId;
}

void MemberAccountingData::setMandateId(QString manadateId)
{
    m_mandateId = manadateId;
    emit mandateIdChanged();
}

QString MemberAccountingData::memberId() const
{
    return m_memberId;
}

void MemberAccountingData::setMemberId(QString memberId)
{
    m_memberId = memberId;
    emit memberIdChanged();
}

QString MemberAccountingData::name() const
{
    return m_name;
}

void MemberAccountingData::setName(QString name)
{
    m_name = name;
    emit nameChanged();
}

QString MemberAccountingData::firstname() const
{
    return m_firstname;
}

void MemberAccountingData::setFirstname(QString firstname)
{
    m_firstname = firstname;
    emit firstnameChanged();
}

QString MemberAccountingData::bankAccountNumber() const
{
    return m_bankAccountNumber;
}

void MemberAccountingData::setBankAccountNumber(QString number)
{
    m_bankAccountNumber = number;
    emit bankAccountNumberChanged();
}

QString MemberAccountingData::bankCode() const
{
    return m_bankCode;
}

void MemberAccountingData::setBankCode(QString code)
{
    m_bankCode = code;
    emit bankCodeChanged();
}

QString MemberAccountingData::sepaBic() const
{
    return m_bic;
}

void MemberAccountingData::setSepaBic(QString bic)
{
    m_bic = bic;
    emit sepaBicChanged();
}

QString MemberAccountingData::sepaIban() const
{
    return m_iban;
}

void MemberAccountingData::setSepaIban(QString iban)
{
    m_iban = iban;
    emit sepaIbanChanged();
}

QDate MemberAccountingData::sepaMandateDate() const
{
    return m_mandateDate;
}

void MemberAccountingData::setSepaMandateDate(QDate date)
{
    m_mandateDate = date;
    emit sepaMandateDateChanged();
}

QString MemberAccountingData::sepaSequenceState() const
{
    return m_sequenceState;
}

void MemberAccountingData::setSepaSequenceState(QString state)
{
    m_sequenceState = state;
    emit sepaSequenceStateChanged();
}

QString MemberAccountingData::accountingReference() const
{
    return m_accountingReference;
}

void MemberAccountingData::setAccountingReference(QString reference)
{
    m_accountingReference = reference;
    emit accountingReferenceChanged();
}

QString MemberAccountingData::purpose() const
{
    return m_purpose;
}

void MemberAccountingData::setPurpose(QString purpose)
{
    m_purpose = purpose;
    emit purposeChanged();
}

QString MemberAccountingData::accountingInfo() const
{
    return m_accountingInfo;
}

void MemberAccountingData::setAccountingInfo(QString info)
{
    m_accountingInfo = info;
    emit accountingInfoChanged();
}

double MemberAccountingData::fee() const
{
    return m_fee;
}

void MemberAccountingData::setFee(double fee)
{
    m_fee = fee;
    emit feeChanged();
}

double MemberAccountingData::donation() const
{
    return m_donation;
}

void MemberAccountingData::setDonation(double donation)
{
    m_donation = donation;
    emit donationChanged();
}

double MemberAccountingData::additionalFee() const
{
    return m_additionalFee;
}

void MemberAccountingData::setAdditionalFee(double fee)
{
    m_additionalFee = fee;
    emit additionalFeeChanged();
}

double MemberAccountingData::additionalDonation() const
{
    return m_additionalDonation;
}

void MemberAccountingData::setAdditionalDonation(double donation)
{
    m_additionalDonation = donation;
    emit additionalDonationChanged();
}

double MemberAccountingData::amortization() const
{
    return m_amortization;
}

void MemberAccountingData::setAmortization(double amortization)
{
    m_amortization = amortization;
    emit amortizationChanged();
}

void MemberAccountingData::setCollectionState(const QChar &state)
{
    m_collectionState = state;
}

bool MemberAccountingData::canCharge() const
{
    return m_collectionState == static_cast<char>(entity::Member::CollectionState::known);
}

} // namespace accounting
} // namespace membermanager
