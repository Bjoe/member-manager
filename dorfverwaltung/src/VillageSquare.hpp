#ifndef VILLAGESQUARE_H
#define VILLAGESQUARE_H

#include <vector>
#include "litesql.hpp"

#include "dorfmanagement.hpp"
#include "Member.hpp"
#include "Balance.hpp"

namespace ClubBackend
{

    class VillageSquare
    {
    public:
        VillageSquare(const MemberManagement::DorfManagement& aDatabase);

        std::vector<Member> sortedBySurename();
        std::vector<Member> sortedByFirstname();
        std::vector<Member> sortedByMemberId();
        std::vector<Member> sortedByNickname();
        std::vector<Member> sortedBy(const litesql::FieldType);

        std::vector<Member> getDeletedMembers();
        Member getMember(const int anId);

        std::vector<Balance> getMemberCashAccount(const int anId);
        //std::vector<Balance> getMemberCashAccount(const ClubMember& aMember);
    protected:
    private:
        MemberManagement::DorfManagement database;
    };
}
#endif // VILLAGESQUARE_H
