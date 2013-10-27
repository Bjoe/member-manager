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
}

void BalancePersistHandler::setMemberId(QString memberId)
{
    m_memberId = memberId;
}

void BalancePersistHandler::setFee(QString fee)
{
    m_fee = fee;
}

void BalancePersistHandler::setDonation(QString donation)
{
    m_donation = donation;
}

void BalancePersistHandler::setAdditional(QString additional)
{
    m_additional = additional;
}

void BalancePersistHandler::setAdditionalDonation(QString additionalDonation)
{
    m_additionalDonation = additionalDonation;
}

void BalancePersistHandler::setTax(QString tax)
{
    m_tax = tax;
}

void BalancePersistHandler::onBooked()
{
    Q_ASSERT(m_cashAccount);
    emit progress(0);
    emit statusMessage("Booking in progress ... please wait");

    qDebug() << "Book on member id: " << m_memberId;
    int memberId = m_memberId.toInt();

    double fee = m_fee.toDouble();
    persistInBalance(memberId, fee, 11);

    double donation = m_donation.toDouble();
    persistInBalance(memberId, donation, 12);

    double additional = m_additional.toDouble();
    persistInBalance(memberId, additional, 4);

    double additionalDonation = m_additionalDonation.toDouble();
    persistInBalance(memberId, additionalDonation, 3);

    double tax = m_tax.toDouble();
    persistInBalance(memberId, tax, 2);

    m_cashAccount->setMemberId(memberId);
    m_cashAccount->setBooked(true);
    m_cashAccount->save();

    emit progress(1);
    emit statusMessage("Booking done.");
    emit memberChanged();
}

void BalancePersistHandler::persistInBalance(int memberId, double value, int account)
{
    qDebug() << "Book for member id "<< memberId << " on account " << account << " value " << value;

    if(value <= 0.0) {
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
