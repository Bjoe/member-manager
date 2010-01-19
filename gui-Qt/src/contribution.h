#ifndef CONTRIBUTION_H
#define CONTRIBUTION_H

#include <string>

namespace ClubFrontend {

class Contribution
{
public:
    virtual ~Contribution() {}
    virtual void setFee(const int&) = 0;
    virtual int getFee() const = 0;
    virtual void setDonation(const int&) = 0;
    virtual int getDonation() const = 0;
    virtual void setInfo(const std::string&) = 0;
    virtual std::string getInfo() const = 0;
    virtual void setValidFrom(const std::string&) = 0;
    virtual std::string getValidFrom() const = 0;
};

}

#endif // CONTRIBUTION_H
