#ifndef RESSOURCEN_H
#define RESSOURCEN_H

#include <vector>
#include <string>

#include "dorfmanagement.hpp"
#include "EMail.hpp"

namespace Dorfverwaltung {

class Ressourcen
{
    public:
        Ressourcen(const MemberManagement::DorfManagement& aDatabase);
        // Wird von litesql::select benoetigt
        Ressourcen(const litesql::Database& aDatabase, const litesql::Record& aRecord);

        // Wird von litesql::select benoetigt
        static void getFieldTypes(std::vector<litesql::FieldType>& aFieldType)
        {
            MemberManagement::Ressourcen::getFieldTypes(aFieldType);
        }

        void setEmailIntern(const EMail& anEmail);
        EMail getEmailIntern() const;

        void setEmailCcc(const EMail& anEmail);
        EMail getEmailCcc() const;

        void setShellAccount(const std::string& anAccount)
        {
            ressourcen.shellAccount = anAccount;
        }

        std::string getShellAccount() const
        {
            return ressourcen.shellAccount;
        }


    protected:
    private:
        MemberManagement::Ressourcen ressourcen;
};
}
#endif // RESSOURCEN_H
