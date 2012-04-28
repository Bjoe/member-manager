#ifndef MEMBER_H
#define MEMBER_H

#include <QtGui>
#include <QtSql>

#include "model/memberdao.h"

namespace membermanager
{
namespace model { class MemberDao; }

/// \todo Refactor, rename to MemberEntry
class Member
{
public:
    Member();
    Member(int aMemberId);

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
    QString getReference() const;
    void setReference(const QString &aReference);
    QString getStreet() const;
    void setStreet(const QString &aStreet);
    QString getCity() const;
    void setCity(const QString &aCity);
    QString getZipCode() const;
    void setZipCode(const QString &aCode);
    bool isCollection() const;
    void setCollection(bool aCollection);
    QString getAccountNr() const;
    void setAccountNr(const QString &aNr);
    QString getBankName() const;
    void setBankName(const QString &aName);
    QString getCode() const;
    void setCode(const QString &aCode);

    bool isDeleted() const;
    void setDeleted(bool aDeleted);

    friend class model::MemberDao;

private:
    QSqlRecord memberRecord;
    QSqlRecord addressRecord;
    QSqlRecord bankRecord;
    QSqlRecord ressourcenRecord;
};

}

#endif // MEMBER_H
