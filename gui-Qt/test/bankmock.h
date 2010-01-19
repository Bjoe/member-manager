#ifndef BANKMOCK_H
#define BANKMOCK_H

#include <string>
#include "../src/bank.h"

namespace ClubFrontendTest {

class BankMock : public ClubFrontend::Bank
{
public:
    BankMock();

    virtual void setAccount(const int& anAccount)
    {
        account = anAccount;
    }

    virtual int getAccount() const
    {
        return account;
    }

    virtual void setName(const std::string& aName)
    {
        name = aName;
    }

    virtual std::string getName() const
    {
        return name;
    }

    virtual void setCode(const int& aCode)
    {
        code = aCode;
    }

    virtual int getCode() const
    {
        return code;
    }

private:
    int account;
    std::string name;
    int code;
};

}

#endif // BANKMOCK_H
