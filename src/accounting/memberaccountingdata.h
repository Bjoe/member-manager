#ifndef MEMBERMANAGER_ACCOUNTING_MEMBERACCOUNTINGDATA_H
#define MEMBERMANAGER_ACCOUNTING_MEMBERACCOUNTINGDATA_H

#include <QObject>
#include <QChar>
#include <QString>
#include <QDate>

namespace membermanager {
namespace accounting {

class MemberAccountingData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate valuta READ valuta WRITE setValuta NOTIFY valutaChanged)
    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString bankAccountNumber READ bankAccountNumber WRITE setBankAccountNumber NOTIFY bankAccountNumberChanged)
    Q_PROPERTY(QString bankCode READ bankCode WRITE setBankCode NOTIFY bankCodeChanged)
    Q_PROPERTY(double fee READ fee WRITE setFee NOTIFY feeChanged)
    Q_PROPERTY(double donation READ donation WRITE setDonation NOTIFY donationChanged)
    Q_PROPERTY(double additionalFee READ additionalFee WRITE setAdditionalFee NOTIFY additionalFeeChanged)
    Q_PROPERTY(double additionalDonation READ additionalDonation WRITE setAdditionalDonation NOTIFY additionalDonationChanged)
    Q_PROPERTY(double amortization READ amortization WRITE setAmortization NOTIFY amortizationChanged)
    Q_PROPERTY(QString purpose READ purpose WRITE setPurpose NOTIFY purposeChanged)
    Q_PROPERTY(QString accountingInfo READ accountingInfo WRITE setAccountingInfo NOTIFY accountingInfoChanged)

public:

    QDate valuta() const;
    void setValuta(const QDate& date);

    QString memberId() const;
    void setMemberId(const QString& memberId);

    QString name() const;
    void setName(const QString& name);

    QString firstname() const;
    void setFirstname(const QString& firstname);

    QString bankAccountNumber() const;
    void setBankAccountNumber(const QString& number);

    QString bankCode() const;
    void setBankCode(const QString& code);

    QString purpose() const;
    void setPurpose(const QString& purpose);

    QString accountingInfo() const;
    void setAccountingInfo(const QString& info);

    double fee() const;
    void setFee(double fee);

    double donation() const;
    void setDonation(double donation);

    double additionalFee() const;
    void setAdditionalFee(double fee);

    double additionalDonation() const;
    void setAdditionalDonation(double donation);

    double amortization() const;
    void setAmortization(double amortization);

    void setCollectionState(const QChar& state);
    bool canCharge() const;

signals:
    void valutaChanged();
    void memberIdChanged();
    void nameChanged();
    void firstnameChanged();
    void bankAccountNumberChanged();
    void bankCodeChanged();
    void feeChanged();
    void donationChanged();
    void additionalFeeChanged();
    void additionalDonationChanged();
    void amortizationChanged();
    void purposeChanged();
    void accountingInfoChanged();

private:
    QDate m_valuta;
    QString m_memberId;
    QString m_name;
    QString m_firstname;
    QString m_bankAccountNumber;
    QString m_bankCode;
    QString m_purpose;
    QString m_accountingInfo;
    double m_fee;
    double m_donation;
    double m_additionalFee;
    double m_additionalDonation;
    double m_amortization;
    QChar m_collectionState;

};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_MEMBERACCOUNTINGDATA_H
