#ifndef MEMBER_H
#define MEMBER_H

#include <QtGui>
#include <QtSql>
#include "model/memberfilter.h"
#include "membercontribution.h"

namespace membermanager
{

class Member
{
public:
    Member();
    Member(const model::MemberFilter &aFilter);

    int getMemberId() const;
    QString getName() const;
    void setName(const QString &aName);
    QString getFirstname() const;
    void setFirstname(const QString &aName);
    QString getNickname() const;
    void setNickname(const QString &aName);
    QString getEmail() const;
    void setEmail(const QString &anEmailAddress);
    QDate getEntryDate() const;
    void setEntryDate(const QDate &aDate);
    QString getInfo() const;
    void setInfo(const QString &anInfo);
    QString getStreet() const;
    void setStreet(const QString &aStreet);
    QString getCity() const;
    void setCity(const QString &aCity);
    QString getZipCode() const;
    void setZipCode(const QString &aCode);
    QString getAccountNr() const;
    void setAccountNr(const QString &aNr);
    QString getBankName() const;
    void setBankName(const QString &aName);
    QString getCode() const;
    void setCode(const QString &aCode);

    bool isDeleted() const;
    void setDeleted(bool aDeleted);

    MemberContribution getMemberContribution() const;

    bool save();

private:
    QSqlRecord memberRecord;
    QSqlRecord addressRecord;
    QSqlRecord bankRecord;
    QSqlRecord ressourcenRecord;
};

}

#endif // MEMBER_H
