#ifndef MEMBERMANAGER_ENTITY_MEMBER_H
#define MEMBERMANAGER_ENTITY_MEMBER_H

#include <QtCore/QString>
#include <QtCore/QDate>
#include <QtCore/QVariant>

#include "QDjangoModel.h"

namespace membermanager {
namespace entity {

class Member : public QDjangoModel
{
    Q_OBJECT

    Q_PROPERTY(long memberId READ memberId WRITE setMemberId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString firstname READ firstname WRITE setFirstname)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname)
    Q_PROPERTY(QString email READ email WRITE setEmail)
    Q_PROPERTY(QDate entryDate READ entryDate WRITE setEntryDate)
    Q_PROPERTY(QDate cancellationDate READ cancellationDate WRITE setCancellationDate)
    Q_PROPERTY(QString info READ info WRITE setInfo)
    Q_PROPERTY(QString reference READ reference WRITE setReference)
    Q_PROPERTY(QString street READ street WRITE setStreet)
    Q_PROPERTY(QString city READ city WRITE setCity)
    Q_PROPERTY(QString zipCode READ zipCode WRITE setZipCode)
    Q_PROPERTY(QVariant collection READ collection WRITE setCollection)
    Q_PROPERTY(QString accountNumber READ accountNumber WRITE setAccountNumber)
    Q_PROPERTY(QString bankName READ bankName WRITE setBankName)
    Q_PROPERTY(QString bankCode READ bankCode WRITE setBankCode)
    Q_PROPERTY(QVariant deleted READ deleted WRITE setDeleted)

public:

    long memberId() const;
    void setMemberId(long id);

    QString name() const;
    void setName(const QString &name);

    QString firstname() const;
    void setFirstname(const QString &name);

    QString nickname() const;
    void setNickname(const QString &name);

    QString email() const;
    void setEmail(const QString &email);

    QDate entryDate() const;
    void setEntryDate(const QDate &date);

    QDate cancellationDate() const;
    void setCancellationDate(const QDate &date);

    QString info() const;
    void setInfo(const QString &info);

    QString reference() const;
    void setReference(const QString &reference);

    QString street() const;
    void setStreet(const QString &street);

    QString city() const;
    void setCity(const QString &city);

    QString zipCode() const;
    void setZipCode(const QString &code);

    QVariant collection() const;
    void setCollection(const QVariant &collection);

    QString accountNumber() const;
    void setAccountNumber(const QString &number);

    QString bankName() const;
    void setBankName(const QString &name);

    QString bankCode() const;
    void setBankCode(const QString &code);

    QVariant deleted() const;
    void setDeleted(const QVariant &deleted);

private:
    long m_memberId;
    QString m_name;
    QString m_firstname;
    QString m_nickname;
    QString m_email;
    QDate m_entryDate;
    QDate m_cancellationDate;
    QString m_info;
    QString m_reference;
    QString m_street;
    QString m_city;
    QString m_zipCode;
    QVariant m_collection;
    QString m_accountNumber;
    QString m_bankName;
    QString m_bankCode;
    QVariant m_deleted;
};

} // namespace entity
} // namespace membermanager

#endif // MEMBERMANAGER_ENTITY_MEMBER_H
