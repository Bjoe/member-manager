#include "balancepersisthandler.h"

#include <QDebug>

#include "entity/balance.h"

namespace membermanager {
namespace gui {

BalancePersistHandler::BalancePersistHandler(QObject *parent) :
    QObject(parent),
    m_cashAccount(nullptr),
    m_memberId("0"),
    m_fee("0"),
    m_donation("0"),
    m_additional("0"),
    m_additionalDonation("0"),
    m_tax("0")
{
}

void BalancePersistHandler::setCashAccount(entity::CashAccount *cashAccount)
{
    m_cashAccount = cashAccount;
    emit cashAccountChanged();
}

entity::CashAccount *BalancePersistHandler::cashAccount() const
{
    return m_cashAccount;
}

void BalancePersistHandler::setMemberId(QString memberId)
{
    m_memberId = memberId;
    emit memberChanged();
}

QString BalancePersistHandler::memberId() const
{
    return m_memberId;
}

void BalancePersistHandler::setFee(QString fee)
{
    m_fee = fee;
    emit feeChanged();
}

QString BalancePersistHandler::fee() const
{
    return m_fee;
}

void BalancePersistHandler::setDonation(QString donation)
{
    m_donation = donation;
    emit donationChanged();
}

QString BalancePersistHandler::donation() const
{
    return m_donation;
}

void BalancePersistHandler::setAdditional(QString additional)
{
    m_additional = additional;
    emit additionalChanged();
}

QString BalancePersistHandler::additional() const
{
    return m_additional;
}

void BalancePersistHandler::setAdditionalDonation(QString additionalDonation)
{
    m_additionalDonation = additionalDonation;
    emit additionalDonationChanged();
}

QString BalancePersistHandler::additionalDonation() const
{
    return m_additionalDonation;
}

void BalancePersistHandler::setTax(QString tax)
{
    m_tax = tax;
    emit taxChanged();
}

QString BalancePersistHandler::tax() const
{
    return m_tax;
}

void BalancePersistHandler::onBooked()
{
    Q_ASSERT(m_cashAccount);
    emit progress(0);
    emit statusMessage("Booking in progress ... please wait");

    qDebug() << "Book on member id: " << m_memberId;

    double fee = m_fee.toDouble();
    persistInBalance(m_memberId, fee, 11);

    double donation = m_donation.toDouble();
    persistInBalance(m_memberId, donation, 12);

    double additional = m_additional.toDouble();
    persistInBalance(m_memberId, additional, 4);

    double additionalDonation = m_additionalDonation.toDouble();
    persistInBalance(m_memberId, additionalDonation, 3);

    double tax = m_tax.toDouble();
    persistInBalance(m_memberId, tax, 2);

    m_cashAccount->setMemberId(m_memberId);
    m_cashAccount->setState("booked");
    m_cashAccount->save();

    emit progress(1);
    emit statusMessage("Booking done.");
    emit memberChanged();
}

void BalancePersistHandler::persistInBalance(QString memberId, double value, int account)
{
    qDebug() << "Book for member id "<< memberId << " on account " << account << " value " << value;

    if(value == 0.0) {
        return;
    }

    entity::Balance *balance = new entity::Balance();
    balance->setMemberId(memberId);
    balance->setCashAccountId(m_cashAccount->cashAccountId());
    balance->setValuta(m_cashAccount->valuta());
    balance->setPurpose(m_cashAccount->purpose());
    balance->setValue(value);
    balance->setAccount(account);
    balance->setInfo("Automatische Buchung");
    balance->save();
    delete balance;
}

} // namespace gui
} // namespace membermanager
