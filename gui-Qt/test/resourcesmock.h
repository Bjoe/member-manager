#ifndef RESOURCESMOCK_H
#define RESOURCESMOCK_H

#include <string>
#include "../src/resources.h"

namespace ClubFrontendTest {

class ResourcesMock : public ClubFrontend::Resources
{
public:
    ResourcesMock();

    virtual void setEmailIntern(const std::string& anEmailIntern)
    {
        emailIntern = anEmailIntern;
    }

    virtual std::string getEmailIntern() const
    {
        return emailIntern;
    }

    virtual void setEmailCCC(const std::string& anEmailCCC)
    {
        emailCCC = anEmailCCC;
    }

    virtual std::string getEmailCCC() const
    {
        return emailCCC;
    }

    virtual void setShellAccount(const std::string& aShellAccount)
    {
        shellAccount = aShellAccount;
    }

    virtual std::string getShellAccount() const
    {
        return shellAccount;
    }

private:
    std::string emailIntern;
    std::string emailCCC;
    std::string shellAccount;
};

}

#endif // RESOURCESMOCK_H
