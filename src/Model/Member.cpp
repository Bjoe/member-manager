#include "Model/Member.h"

namespace ClubFrontend
{

Member::Member() :
        id ( 0 ), name ( "" ), firstname ( "" ), nickname ( "" ), donation ( 0 ), fee ( 0 )
{

}

Member::Member ( const int anId, const QString& aName, const QString& aFirstname, const QString& aNickname, const float aDonation, const float aFee ) :
        id ( anId ), name ( aName ), firstname ( aFirstname ), nickname ( aNickname ), donation ( aDonation ), fee ( aFee )
{

}

int Member::getMemberId() const
{
    return id;
}

QString Member::getFirstname() const
{
    return firstname;
}

QString Member::getName() const
{
    return name;
}

QString Member::getNickname() const
{
    return nickname;
}

float Member::getDonation() const
{
    return donation;
}

float Member::getFee() const
{
    return fee;
}

}
