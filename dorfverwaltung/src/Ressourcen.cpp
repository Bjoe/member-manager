#include "Ressourcen.hpp"

namespace Dorfverwaltung
{

    Ressourcen::Ressourcen(const MemberManagement::DorfManagement& aDatabase) : ressourcen(aDatabase)
    {
        //ctor
    }

    Ressourcen::Ressourcen(const litesql::Database& aDatabase, const litesql::Record& aRecord) : ressourcen(aDatabase, aRecord)
    {
    }

    void Ressourcen::setEmailIntern(const EMail& anEmail)
    {
        ressourcen.emailIntern = anEmail.getAddress();
    }

    EMail Ressourcen::getEmailIntern() const
    {
        return EMail(ressourcen.emailIntern);
    }

    void Ressourcen::setEmailCcc(const EMail& anEmail)
    {
        ressourcen.emailCCC = anEmail.getAddress();
    }

    EMail Ressourcen::getEmailCcc() const
    {
        return EMail(ressourcen.emailCCC);
    }
}
