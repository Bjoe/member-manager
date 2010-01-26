#include "VillageSquare.hpp"

namespace ClubBackend
{
    using MemberManagement::Member;
    using MemberManagement::BalanceRl;

    VillageSquare::VillageSquare(const MemberManagement::DorfManagement& aDatabase) : database(aDatabase)
    {

    }

    std::vector<ClubMember> VillageSquare::sortedBy(const litesql::FieldType aType)
    {
        return litesql::select<ClubMember>(database, Member::Deleted == false).orderBy(aType).all();
    }

    std::vector<ClubMember> VillageSquare::sortedBySurename()
    {
        return sortedBy(Member::Surename);
    }

    std::vector<ClubMember> VillageSquare::sortedByFirstname()
    {
        return sortedBy(Member::FirstName);
    }

    std::vector<ClubMember> VillageSquare::sortedByNickname()
    {
        return sortedBy(Member::Nickname);
    }

    std::vector<ClubMember> VillageSquare::sortedByMemberId()
    {
        return sortedBy(Member::MemberId);
    }

    std::vector<ClubMember> VillageSquare::getDeletedMembers()
    {
        return litesql::select<ClubMember>(database, Member::Deleted == true).orderBy(Member::Surename).all();
    }

    ClubMember VillageSquare::getMember(const int anId)
    {
        return litesql::select<ClubMember>(database, Member::MemberId == anId).one();
    }

    std::vector<Balance> VillageSquare::getMemberCashAccount(const int anId)
    {
        Member member = litesql::select<Member>(database, Member::MemberId == anId).one();
        return BalanceRl::get<Balance>(database, litesql::Expr(), BalanceRl::Member == member.id ).all();
    }
}
