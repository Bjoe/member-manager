#include "VillageSquare.hpp"

namespace ClubBackend
{
    VillageSquare::VillageSquare(const MemberManagement::DorfManagement& aDatabase) : database(aDatabase)
    {

    }

    std::vector<Member> VillageSquare::sortedBy(const litesql::FieldType aType)
    {
        return litesql::select<Member>(database, MemberManagement::Member::Deleted == false).orderBy(aType).all();
    }

    std::vector<Member> VillageSquare::sortedBySurename()
    {
        return sortedBy(MemberManagement::Member::Surename);
    }

    std::vector<Member> VillageSquare::sortedByFirstname()
    {
        return sortedBy(MemberManagement::Member::FirstName);
    }

    std::vector<Member> VillageSquare::sortedByNickname()
    {
        return sortedBy(MemberManagement::Member::Nickname);
    }

    std::vector<Member> VillageSquare::sortedByMemberId()
    {
        return sortedBy(MemberManagement::Member::MemberId);
    }

    std::vector<Member> VillageSquare::getDeletedMembers()
    {
        return litesql::select<Member>(database, MemberManagement::Member::Deleted == true).orderBy(MemberManagement::Member::Surename).all();
    }

    Member VillageSquare::getMember(const int anId)
    {
        return litesql::select<Member>(database, MemberManagement::Member::MemberId == anId).one();
    }

    std::vector<Balance> VillageSquare::getMemberCashAccount(const int anId)
    {
        MemberManagement::Member member = litesql::select<MemberManagement::Member>(database, MemberManagement::Member::MemberId == anId).one();
        return MemberManagement::BalanceRl::get<Balance>(database, litesql::Expr(), MemberManagement::BalanceRl::Member == member.id ).all();
    }
}
