#include "balancepersisthandler.h"

#include "entity/balance.h"

namespace membermanager {
namespace gui {

BalancePersistHandler::BalancePersistHandler(QObject *parent) :
    QObject(parent), m_cashAccount(nullptr), m_memberId("0"), m_fee("0"), m_donation("0"), m_tax("0")
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

void BalancePersistHandler::setTax(QString tax)
{
    m_tax = tax;
}

void BalancePersistHandler::onBooked()
{
    int memberId = m_memberId.toInt();

    double fee = m_fee.toDouble();
    persistInBalance(memberId, fee, 11);

    double donation = m_donation.toDouble();
    persistInBalance(memberId, donation, 12);

    double additional = m_additional.toDouble();
    persistInBalance(memberId, additional, 4);

    double tax = m_tax.toDouble();
    persistInBalance(memberId, tax, 3);

    m_cashAccount->setMemberId(memberId);
    m_cashAccount->setBooked(true);
    m_cashAccount->save();
}

void BalancePersistHandler::persistInBalance(int memberId, double value, int account)
{
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