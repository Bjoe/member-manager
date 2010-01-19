#include "EMail.hpp"

namespace Dorfverwaltung
{

    EMail::EMail(const std::string& anEmail) : address(anEmail)
    {
        const boost::regex expr(".*@.*\\.[A-z]{2}$");
        if (! boost::regex_match(address, expr))
        {
            throw EMailException::EMailException("EMail Adresse ist Fehlerhaft");
        }
    }

    EMail::~EMail()
    {
    }
}
