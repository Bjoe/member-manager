#ifndef MEMBERMANAGER_ACCOUNTING_MEMBERDEBT_H
#define MEMBERMANAGER_ACCOUNTING_MEMBERDEBT_H

#include <QObject>
#include <QString>

namespace membermanager {
namespace accounting {

class MemberDebt : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname NOTIFY firstnameChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(double debit READ debit WRITE setDebit NOTIFY debitChanged)

public:
    MemberDebt(QObject *parent = nullptr);

    QString memberId() const;
    void setMemberId(const QString &memberId);

    QString email() const;
    void setEmail(const QString &email);

    QString firstname() const;
    void setFirstname(const QString &firstname);

    QString name() const;
    void setName(const QString &name);

    double debit() const;
    void setDebit(double debit);

signals:
    void memberIdChanged();
    void emailChanged();
    void firstnameChanged();
    void nameChanged();
    void debitChanged();

private:
    QString m_memberId;
    QString m_email;
    QString m_firstname;
    QString m_name;
    double m_debit;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_MEMBERDEBT_H
