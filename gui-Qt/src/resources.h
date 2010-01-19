#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

namespace ClubFrontend {

class Resources
{
public:
    virtual ~Resources() {}
    virtual void setEmailIntern(const std::string&) = 0;
    virtual std::string getEmailIntern() const = 0;
    virtual void setEmailCCC(const std::string&) = 0;
    virtual std::string getEmailCCC() const = 0;
    virtual void setShellAccount(const std::string&) = 0;
    virtual std::string getShellAccount() const = 0;
};

}

#endif // RESOURCES_H
