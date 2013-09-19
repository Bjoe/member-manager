#ifndef MEMBERMANAGER_ENTITY_CONTRIBUTION_H
#define MEMBERMANAGER_ENTITY_CONTRIBUTION_H

#include <QtCore/QString>
#include <QtCore/QDate>

#include "QDjangoModel.h"

namespace membermanager {
namespace entity {

class Contribution : public QDjangoModel
{
    Q_OBJECT

    Q_CLASSINFO("__meta__", "db_table=Contribution")
    Q_CLASSINFO("contributionId", "primary_key=true db_index=true unique=true auto_increment=true")
    Q_CLASSINFO("info", "null=true")

    Q_PROPERTY(int contributionId READ contributionId WRITE setContributionId)
    Q_PROPERTY(int memberId READ memberId WRITE setMemberId)
    Q_PROPERTY(double fee READ fee WRITE setFee)
    Q_PROPERTY(double additionalFee READ additionalFee WRITE setAdditionalFee)
    Q_PROPERTY(double additionalDonation READ additionalDonation WRITE setAdditionalDonation)
    Q_PROPERTY(double donation READ donation WRITE setDonation)
    Q_PROPERTY(double amortization READ amortization WRITE setAmortization)
    Q_PROPERTY(QDate validFrom READ validFrom WRITE setValidFrom)
    Q_PROPERTY(QString info READ info WRITE setInfo)

public:

    int contributionId() const;
    void setContributionId(int id);

    int memberId() const;
    void setMemberId(int id);

    double fee() const;
    void setFee(double fee);

    double additionalFee() const;
    void setAdditionalFee(double fee);

    double additionalDonation() const;
    void setAdditionalDonation(double donation);

    double donation() const;
    void setDonation(double donation);

    double amortization() const;
    void setAmortization(double amortization);

    QString info() const;
    void setInfo(const QString &text);

    QDate validFrom() const;
    void setValidFrom(const QDate &date);

private:
    QString m_info;
    QDate m_validFrom;
    double m_fee;
    double m_additionalFee;
    double m_additionalDonation;
    double m_donation;
    double m_amortization;
    int m_contributionId;
    int m_memberId;
};

} // namespace entity
} // namespace membermanager

#endif // MEMBERMANAGER_ENTITY_CONTRIBUTION_H
