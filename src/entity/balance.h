#ifndef MEMBERMANAGER_ENTITY_BALANCE_H
#define MEMBERMANAGER_ENTITY_BALANCE_H

#include <QtCore/QString>
#include <QtCore/QDate>

#include "QDjangoModel.h"

namespace membermanager {
namespace entity {

class Balance : public QDjangoModel
{
    Q_OBJECT

    Q_CLASSINFO("__meta__", "db_table=Balance")
    Q_CLASSINFO("balanceId", "primary_key=true db_index=true unique=true auto_increment=true")
    Q_CLASSINFO("cashAccountId", "null=true")
    Q_CLASSINFO("info", "null=true")

    Q_PROPERTY(int balanceId READ balanceId WRITE setBalanceId NOTIFY balanceIdChanged)
    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QDate valuta READ valuta WRITE setValuta NOTIFY valutaChanged)
    Q_PROPERTY(QString purpose READ purpose WRITE setPurpose NOTIFY purposeChanged)
    Q_PROPERTY(int account READ account WRITE setAccount NOTIFY accountChanged)
    Q_PROPERTY(int cashAccountId READ cashAccountId WRITE setCashAccountId NOTIFY cashAccountIdChanged)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged)

public:

    int balanceId() const;
    void setBalanceId(int id);

    QString memberId() const;
    void setMemberId(QString id);

    double value() const;
    void setValue(double value);

    QDate valuta() const;
    void setValuta(const QDate &date);

    QString purpose() const;
    void setPurpose(const QString &purpose);

    int account() const;
    void setAccount(int account);

    int cashAccountId() const;
    void setCashAccountId(int id);

    QString info() const;
    void setInfo(const QString &info);

signals:
    void balanceIdChanged();
    void memberIdChanged();
    void valueChanged();
    void valutaChanged();
    void purposeChanged();
    void accountChanged();
    void cashAccountIdChanged();
    void infoChanged();

private:
    QString m_memberId {};
    QString m_info {};
    QString m_purpose {};
    QDate m_valuta {};
    double m_value {};
    int m_account {};
    int m_cashAccountId {};
    int m_balanceId {};
};

} // namespace entity
} // namespace membermanager

#endif // MEMBERMANAGER_ENTITY_BALANCE_H
