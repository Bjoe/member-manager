#ifndef MEMBER_H
#define MEMBER_H

#include <string>

namespace ClubFrontend {

class Member
{
public:
    virtual ~Member() {}
    virtual void setId(const int&) = 0;
    virtual int getId() const = 0;
    virtual void setName(const std::string&) = 0;
    virtual std::string getName() const = 0;
    virtual void setFirstname(const std::string&) = 0;
    virtual std::string getFirstname() const = 0;
    virtual void setNickname(const std::string&) = 0;
    virtual std::string getNickname() const = 0;
    virtual void setEmail(const std::string&) = 0;
    virtual std::string getEmail() const = 0;
    virtual void setCity(const std::string&) = 0;
    virtual std::string getCity() const = 0;
    virtual void setZipCode(const int&) = 0;
    virtual int getZipCode() const = 0;
    virtual void setStreet(const std::string&) = 0;
    virtual std::string getStreet() const = 0;
    virtual void setEntryDate(const std::string&) = 0;
    virtual std::string getEntryDate() const = 0;
    virtual void setInfo(const std::string&) = 0;
    virtual std::string getInfo() const = 0;
};

}

#endif // MEMBER_H
