#ifndef CONTRIBUTIONMOCK_H
#define CONTRIBUTIONMOCK_H

#include <string>
#include "../src/contribution.h"

namespace ClubFrontendTest {

class ContributionMock : public ClubFrontend::Contribution
{
public:
    ContributionMock();

    virtual void setFee(const int& aFee)
    {
        fee = aFee;
    }

    virtual int getFee() const
    {
        return fee;
    }

    virtual void setDonation(const int& aDonation)
    {
        donation = aDonation;
    }

    virtual int getDonation() const
    {
        return donation;
    }

    virtual void setInfo(const std::string& anInfo)
    {
        info = anInfo;
    }

    virtual std::string getInfo() const
    {
        return info;
    }

    virtual void setValidFrom(const std::string& aValidFrom)
    {
        validFrom = aValidFrom;
    }

    virtual std::string getValidFrom() const
    {
        return validFrom;
    }

private:
    int fee;
    int donation;
    std::string info;
    std::string validFrom;
};

}

#endif // CONTRIBUTIONMOCK_H
