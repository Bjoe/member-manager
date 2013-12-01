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

    Q_PROPERTY(int contributionId READ contributionId WRITE setContributionId NOTIFY contributionIdChanged)
    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
    Q_PROPERTY(double fee READ fee WRITE setFee NOTIFY feeChanged)
    Q_PROPERTY(double additionalFee READ additionalFee WRITE setAdditionalFee NOTIFY additionalFeeChanged)
    Q_PROPERTY(double additionalDonation READ additionalDonation WRITE setAdditionalDonation NOTIFY additionalDonationChanged)
    Q_PROPERTY(double donation READ donation WRITE setDonation NOTIFY donationChanged)
    Q_PROPERTY(double amortization READ amortization WRITE setAmortization NOTIFY amortizationChanged)
    Q_PROPERTY(QDate validFrom READ validFrom WRITE setValidFrom NOTIFY validFromChanged)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)

public:

    int contributionId() const;
    void setContributionId(int id);

    QString memberId() const;
    void setMemberId(QString id);

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

signals:
    void contributionIdChanged();
    void memberIdChanged();
    void feeChanged();
    void additionalFeeChanged();
    void additionalDonationChanged();
    void donationChanged();
    void amortizationChanged();
    void validFromChanged();
    void infoChanged();

private:
    QString m_memberId {};
    QString m_info {};
    QDate m_validFrom {};
    double m_fee {};
    double m_additionalFee {};
    double m_additionalDonation {};
    double m_donation {};
    double m_amortization {};
    int m_contributionId {};
};

} // namespace entity
} // namespace membermanager

#endif // MEMBERMANAGER_ENTITY_CONTRIBUTION_H
