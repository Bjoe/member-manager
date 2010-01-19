#ifndef CONTRIBUTION_H
#define CONTRIBUTION_H

#include <vector>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "dorfmanagement.hpp"

namespace Dorfverwaltung {

class Contribution
{
    public:
        Contribution(const MemberManagement::DorfManagement& aDatabase);
        // Wird von litesql::select benoetigt
        Contribution(const litesql::Database& aDatabase, const litesql::Record& aRecord);

        // Wird von litesql::select benoetigt
        static void getFieldTypes(std::vector<litesql::FieldType>& aFieldType)
        {
            MemberManagement::Contribution::getFieldTypes(aFieldType);
        }

        void setFee(const int& aFee)
        {
            contribution.fee = aFee;
        }

        int getFee() const
        {
            return contribution.fee;
        }

        void setDonation(const int& aDonation)
        {
            contribution.donation = aDonation;
        }

        int getDonation() const
        {
            return contribution.donation;
        }

        void setInfo(const std::string& anInfo)
        {
            contribution.info = anInfo;
        }

        std::string getInfo() const
        {
            return contribution.info;
        }

        void setValidFrom(const boost::gregorian::date& aDate);
        boost::gregorian::date getValidFrom() const;

    protected:
    private:
        MemberManagement::Contribution contribution;
};
}
#endif // CONTRIBUTION_H
