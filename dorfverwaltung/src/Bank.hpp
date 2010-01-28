#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

#include "../src/dorfmanagement.hpp"

namespace ClubBackend
{

class Bank
{
public:
	Bank(const MemberManagement::DorfManagement& aDatabase);
	// Wind von litesql::select benoetigt
	Bank(const litesql::Database& aDatabase, const litesql::Record& aRecord);

	// Wird von litesql::select benoetigt
	static void getFieldTypes(std::vector<litesql::FieldType>& aFtypes) {
		MemberManagement::Bank::getFieldTypes(aFtypes);
	}

	void setAccount(const int& anAccount) {
		bankAccount.account = anAccount;
	}

	int getAccount() const {
		return bankAccount.account;
	}

	void setName(const std::string& aName) {
		bankAccount.name = aName;
	}

	std::string getName() const {
		return bankAccount.name;
	}


	void setCode(const int& aCode) {
		bankAccount.code = aCode;
	}

	int getCode() const {
		return bankAccount.code;
	}


protected:
private:

	MemberManagement::Bank bankAccount;

};
}

#endif // BANK_H
