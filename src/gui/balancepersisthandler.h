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

    Q_PROPERTY(membermanager::entity::CashAccount *cashAccount WRITE setCashAccount)
    Q_PROPERTY(QString memberId WRITE setMemberId)
    Q_PROPERTY(QString fee WRITE setFee)
    Q_PROPERTY(QString donation WRITE setDonation)
    Q_PROPERTY(QString additional WRITE setAdditional)
    Q_PROPERTY(QString additionalDonation WRITE setAdditionalDonation)
    Q_PROPERTY(QString tax WRITE setTax)

public:
    explicit BalancePersistHandler(QObject *parent = 0);

    void setCashAccount(entity::CashAccount *cashAccount);
    void setMemberId(QString memberId);
    void setFee(QString fee);
    void setDonation(QString donation);
    void setAdditional(QString additional);
    void setAdditionalDonation(QString additionalDonation);
    void setTax(QString tax);

signals:

public slots:
    void onBooked();

private:
    entity::CashAccount *m_cashAccount;
    QString m_memberId;
    QString m_fee;
    QString m_donation;
    QString m_additional;
    QString m_additionalDonation;
    QString m_tax;

    void persistInBalance(int memberId, double value, int account);
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_BALANCEPERSISTHANDLER_H
