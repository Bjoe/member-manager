#ifndef MEMBERMANAGER_ENTITY_CASHACCOUNT_H
#define MEMBERMANAGER_ENTITY_CASHACCOUNT_H

#include <QString>
#include <QDate>

#include "QDjangoModel.h"

namespace membermanager {
namespace entity {

class CashAccount : public QDjangoModel
{
    Q_OBJECT

    Q_CLASSINFO("__meta__", "db_table=CashAccount")
    Q_CLASSINFO("cashAccountId", "primary_key=true db_index=true unique=true auto_increment=true")
    Q_CLASSINFO("memberId", "null=true")
    Q_CLASSINFO("remoteName", "null=true")
    Q_CLASSINFO("remoteAccountNumber", "null=true")

    Q_PROPERTY(int cashAccountId READ cashAccountId WRITE setCashAccountId)
    Q_PROPERTY(QString primanota READ primanota WRITE setPrimanota)
    Q_PROPERTY(QDate valuta READ valuta WRITE setValuta)
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int transactionCode READ transactionCode WRITE setTransactionCode)
    Q_PROPERTY(QString transactionText READ transactionText WRITE setTransactionText)
    Q_PROPERTY(QString remoteName READ remoteName WRITE setRemoteName)
    Q_PROPERTY(QString remoteBankCode READ remoteBankCode WRITE setRemoteBankCode)
    Q_PROPERTY(QString remoteAccountNumber READ remoteAccountNumber WRITE setRemoteAccountNumber)
    Q_PROPERTY(QString purpose READ purpose WRITE setPurpose)
    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId)
    Q_PROPERTY(QString state READ state WRITE setState)

public:

    int cashAccountId() const;
    void setCashAccountId(int id);

    QString primanota() const;
    void setPrimanota(const QString &primanota);

    QDate valuta() const;
    void setValuta(const QDate &valuta);

    QDate date() const;
    void setDate(const QDate &date);

    double value() const;
    void setValue(double value);

    int transactionCode() const;
    void setTransactionCode(int code);

    QString transactionText() const;
    void setTransactionText(const QString &text);

    QString remoteName() const;
    void setRemoteName(const QString &name);

    QString remoteBankCode() const;
    void setRemoteBankCode(const QString &code);

    QString remoteAccountNumber() const;
    void setRemoteAccountNumber(const QString &number);

    QString purpose() const;
    void setPurpose(const QString &text);

    QString memberId() const;
    void setMemberId(QString id);

    QString state() const;
    void setState(QString state);

private:
    QString m_primanota {};
    QString m_transactionText {};
    QString m_remoteName {};
    QString m_remoteBankCode {};
    QString m_remoteAccountNumber {};
    QString m_purpose {};
    QString m_memberId {};
    QString m_state {};
    QDate m_valuta {};
    QDate m_date {};
    double m_value {};
    int m_transactionCode {};
    int m_cashAccountId {};
};

} // namespace entity
} // namespace membermanager

#endif // MEMBERMANAGER_ENTITY_CASHACCOUNT_H
