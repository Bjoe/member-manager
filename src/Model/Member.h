#ifndef MEMBER_H
#define MEMBER_H

#include <QString>

namespace ClubFrontend
{

class Member
{
public:
    Member();
    Member ( const int anId, const QString &aName, const QString &aFirstname, const QString &aNickname,
             const float aDonation, const float aFee );

    int getMemberId() const;
    QString getName() const;
    QString getFirstname() const;
    QString getNickname() const;
    float getDonation() const;
    float getFee() const;

private:
    int id;
    QString name;
    QString firstname;
    QString nickname;
    float donation;
    float fee;

};

}

#endif // MEMBER_H
