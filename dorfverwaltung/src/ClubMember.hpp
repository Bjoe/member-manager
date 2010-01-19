/***************************************************************************
 *            mitglied.hpp
 *
 *  Fri Apr  3 07:34:14 2009
 *  Copyright  2009  joerg
 *  <joerg@<host>>
 ****************************************************************************/

#ifndef _CLUB_MEMBER_HPP_
#define _CLUB_MEMBER_HPP_

#include <iostream>
#include <litesql.hpp>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "dorfmanagement.hpp"
#include "EMail.hpp"

namespace Dorfverwaltung
{

    class ClubMember
    {

    private:
        MemberManagement::Member member;

    public:
        ClubMember(const MemberManagement::DorfManagement& aDatabase);
        // Wird von litesql::select benoetigt
        ClubMember(const litesql::Database& aDatabase, const litesql::Record& aRecord);

        // Wird von litesql::select benoetigt
        static void getFieldTypes(std::vector<litesql::FieldType>& aFtypes)
        {
            MemberManagement::Member::getFieldTypes(aFtypes);
        }

        MemberManagement::Member::MoneyHandle money()
        {
            return member.money();
        }

        MemberManagement::Member::InternalRessourcenHandle internalRessourcen()
        {
            return member.internalRessourcen();
        }

        MemberManagement::Member::BankAccountHandle bankAccount()
        {
            return member.bankAccount();
        }

        MemberManagement::Member::CashAccountHandle cashAccount()
        {
            return member.cashAccount();
        }

        void setEntryDate(const boost::gregorian::date& anEntryDate);
        boost::gregorian::date getEntryDate() const;

        void setLeavingDate(const boost::gregorian::date& anLeavingDate);
        boost::gregorian::date getLeavingDate() const;

        void setEmail(const EMail::EMail& anEmailAdr);
        EMail::EMail getEmail() const;

        void setId(const int& anId)
        {
            member.memberId = anId;
        }

        int getId() const
        {
            return member.memberId;
        }

        void setDeleted(const bool& aDeleted)
        {
            member.deleted = aDeleted;
        }

        bool getDeleted() const
        {
            return member.deleted;
        }

        void setCashCollection(const bool& aCashCollection)
        {
            member.cashCollection = aCashCollection;
        }

        bool getCashCollection() const
        {
            return member.cashCollection;
        }

        void setName(const std::string& aName)
        {
            member.surename = aName;
        }

        std::string getName() const
        {
            return member.surename;
        }

        void setFirstname(const std::string& aName)
        {
            member.firstName = aName;
        }

        std::string getFirstname() const
        {
            return member.firstName;
        }

        void setNickname(const std::string& aNickname)
        {
            member.nickname = aNickname;
        }

        std::string getNickname() const
        {
            return member.nickname;
        }

        void setStreet(const std::string& aStreet)
        {
            member.street = aStreet;
        }

        std::string getStreet() const
        {
            return member.street;
        }

        void setZipCode(const int& aZipCode)
        {
            member.zipCode = aZipCode;
        }

        int getZipCode() const
        {
            return member.zipCode;
        }

        void setCity(const std::string& aCity)
        {
            member.city = aCity;
        }

        std::string getCity() const
        {
            return member.city;
        }

        void setInfo(const std::string& anInfo)
        {
            member.info = anInfo;
        }

        std::string getInfo() const
        {
            return member.info;
        }
    };
}

#endif // _MCLUB_MEMBER_HPP_
