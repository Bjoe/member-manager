#ifndef VILLAGESQUARE_H
#define VILLAGESQUARE_H

#include <vector>
#include "litesql.hpp"

#include "dorfmanagement.hpp"
#include "ClubMember.hpp"
#include "Balance.hpp"

namespace Dorfverwaltung
{

    class VillageSquare
    {
    public:
        VillageSquare(const MemberManagement::DorfManagement& aDatabase);

        std::vector<ClubMember> sortedBySurename();
        std::vector<ClubMember> sortedByFirstname();
        std::vector<ClubMember> sortedByMemberId();
        std::vector<ClubMember> sortedByNickname();
        std::vector<ClubMember> sortedBy(const litesql::FieldType);

        std::vector<ClubMember> getDeletedMembers();
        ClubMember getMember(const int anId);

        std::vector<Balance> getMemberCashAccount(const int anId);
        //std::vector<Balance> getMemberCashAccount(const ClubMember& aMember);
    protected:
    private:
        MemberManagement::DorfManagement database;
    };
}
#endif // VILLAGESQUARE_H
