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
    Q_PROPERTY(QString mandateId READ mandateId WRITE setMandateId NOTIFY mandateIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString bankAccountNumber READ bankAccountNumber WRITE setBankAccountNumber NOTIFY bankAccountNumberChanged)
    Q_PROPERTY(QString bankCode READ bankCode WRITE setBankCode NOTIFY bankCodeChanged)
    Q_PROPERTY(QString sepaBic READ sepaBic WRITE setSepaBic NOTIFY sepaBicChanged)
    Q_PROPERTY(QString sepaIban READ sepaIban WRITE setSepaIban NOTIFY sepaIbanChanged)
    Q_PROPERTY(QDate sepaMandateDate READ sepaMandateDate WRITE setSepaMandateDate NOTIFY sepaMandateDateChanged)
    Q_PROPERTY(QString sepaSequenceState READ sepaSequenceState WRITE setSepaSequenceState NOTIFY sepaSequenceStateChanged)
    Q_PROPERTY(QString accountingReference READ accountingReference WRITE setAccountingReference NOTIFY accountingReferenceChanged)
    Q_PROPERTY(double fee READ fee WRITE setFee NOTIFY feeChanged)
    Q_PROPERTY(double donation READ donation WRITE setDonation NOTIFY donationChanged)
    Q_PROPERTY(double additionalFee READ additionalFee WRITE setAdditionalFee NOTIFY additionalFeeChanged)
    Q_PROPERTY(double additionalDonation READ additionalDonation WRITE setAdditionalDonation NOTIFY additionalDonationChanged)
    Q_PROPERTY(double amortization READ amortization WRITE setAmortization NOTIFY amortizationChanged)
    Q_PROPERTY(QString purpose READ purpose WRITE setPurpose NOTIFY purposeChanged)
    Q_PROPERTY(QString accountingInfo READ accountingInfo WRITE setAccountingInfo NOTIFY accountingInfoChanged)

public:
    MemberAccountingData(QObject* parent = nullptr);

    QDate valuta() const;
    void setValuta(QDate date);

    QString mandateId() const;
    void setMandateId(QString manadateId);

    QString name() const;
    void setName(QString name);

    QString firstname() const;
    void setFirstname(QString firstname);

    QString bankAccountNumber() const;
    void setBankAccountNumber(QString number);

    QString bankCode() const;
    void setBankCode(QString code);

    QString sepaBic() const;
    void setSepaBic(QString bic);

    QString sepaIban() const;
    void setSepaIban(QString iban);

    QDate sepaMandateDate() const;
    void setSepaMandateDate(QDate date);

    QString sepaSequenceState() const;
    void setSepaSequenceState(QString state);

    QString accountingReference() const;
    void setAccountingReference(QString reference);

    QString purpose() const;
    void setPurpose(QString purpose);

    QString accountingInfo() const;
    void setAccountingInfo(QString info);

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
    void mandateIdChanged();
    void nameChanged();
    void firstnameChanged();
    void bankAccountNumberChanged();
    void bankCodeChanged();
    void sepaBicChanged();
    void sepaIbanChanged();
    void sepaMandateDateChanged();
    void sepaSequenceStateChanged();
    void accountingReferenceChanged();
    void feeChanged();
    void donationChanged();
    void additionalFeeChanged();
    void additionalDonationChanged();
    void amortizationChanged();
    void purposeChanged();
    void accountingInfoChanged();

private:
    QDate m_valuta;
    QString m_mandateId;
    QString m_name;
    QString m_firstname;
    QString m_bankAccountNumber;
    QString m_bankCode;
    QString m_bic;
    QString m_iban;
    QDate m_mandateDate;
    QString m_sequenceState;
    QString m_accountingReference;
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
