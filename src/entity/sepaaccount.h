#ifndef MEMBERMANAGER_ENTITY_SEPAACCOUNT_H
#define MEMBERMANAGER_ENTITY_SEPAACCOUNT_H

#include <QObject>
#include <QString>
#include <QDate>

#include "QDjangoModel.h"

namespace membermanager {
namespace entity {

class SepaAccount : public QDjangoModel
{
    Q_OBJECT

    Q_CLASSINFO("__meta__", "db_table=CashAccount")

    Q_PROPERTY(QString iban READ iban WRITE setIban)
    Q_PROPERTY(QString bic READ bic WRITE setBic)
    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId)
    Q_PROPERTY(QString sequenceState READ sequenceState WRITE setSequenceState)
    Q_PROPERTY(QDate mandateDate READ mandateDate WRITE setMandateDate)

public:

    QString iban() const;
    void setIban(QString iban);

    QString bic() const;
    void setBic(QString bic);

    QDate mandateDate() const;
    void setMandateDate(QDate date);

    QString memberId() const;
    void setMemberId(QString id);

    QString sequenceState() const;
    void setSequenceState(QString sequenceState);

private:
    QString m_iban;
    QString m_bic;
    QString m_memberId;
    QString m_sequenceState;
    QDate m_mandateDate;
};

} // namespace entity
} // namespace membermanager

#endif // MEMBERMANAGER_ENTITY_SEPAACCOUNT_H
