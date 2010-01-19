#ifndef __email__
#define __email__

#include <string>
#include <exception>
#include <boost/regex.hpp>

#include "../src/EMailException.hpp"

namespace Dorfverwaltung
{

    class EMail
    {
    private:
        std::string address;

    public:
        EMail(const std::string& anEmail);
        virtual ~EMail();

        std::string getAddress() const
        {
            return address;
        }

    };
}

#endif // __email__
