#ifndef MEMBERMANAGER_GUI_BALANCEPERSISTHANDLER_H
#define MEMBERMANAGER_GUI_BALANCEPERSISTHANDLER_H

#include <QObject>
#include <QString>

#include "entity/cashaccount.h"

namespace membermanager {
namespace gui {

class BalancePersistHandler : public QObject
{
    Q_OBJECT

    Q_ENUMS(State)

    Q_PROPERTY(membermanager::entity::CashAccount *cashAccount READ cashAccount WRITE setCashAccount NOTIFY cashAccountChanged)
    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
    Q_PROPERTY(QString fee READ fee WRITE setFee NOTIFY feeChanged)
    Q_PROPERTY(QString donation READ donation WRITE setDonation NOTIFY donationChanged)
    Q_PROPERTY(QString additional READ additional WRITE setAdditional NOTIFY additionalChanged)
    Q_PROPERTY(QString additionalDonation READ additionalDonation WRITE setAdditionalDonation NOTIFY additionalDonationChanged)
    Q_PROPERTY(QString tax READ tax WRITE setTax NOTIFY taxChanged)

public:
    enum class State { OK, WRONGVALUE, ISBOOKED };

    explicit BalancePersistHandler(QObject *parent = 0);

    void setCashAccount(entity::CashAccount *cashAccount);
    entity::CashAccount *cashAccount() const;

    void setMemberId(QString memberId);
    QString memberId() const;

    void setFee(QString fee);
    QString fee() const;

    void setDonation(QString donation);
    QString donation() const;

    void setAdditional(QString additional);
    QString additional() const;

    void setAdditionalDonation(QString additionalDonation);
    QString additionalDonation() const;

    void setTax(QString tax);
    QString tax() const;

    Q_INVOKABLE State book();

signals:
    void cashAccountChanged();
    void memberIdChanged();
    void feeChanged();
    void donationChanged();
    void additionalChanged();
    void additionalDonationChanged();
    void taxChanged();

    void statusMessage(QString message);
    void progress(double value);

private:
    entity::CashAccount *m_cashAccount = nullptr;
    QString m_memberId = QString("0");
    QString m_fee = QString("0");
    QString m_donation = QString("0");
    QString m_additional = QString("0");
    QString m_additionalDonation = QString("0");
    QString m_tax = QString("0");

    void persistInBalance(QString memberId, double value, int account);
    State verifySum();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_BALANCEPERSISTHANDLER_H
