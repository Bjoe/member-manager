/*
 * DatabaseStructure.h
 *
 *  Created on: Jul 22, 2010
 *      Author: joerg
 */

#ifndef DATABASESTRUCTURE_H_
#define DATABASESTRUCTURE_H_

#include <QString>

namespace ClubFrontend {



class AddressTable
{
public:
	static const QString TABLENAME;
	enum column { AddressId, MemberId, Street, ZipCode, Town };
};



class ContributionTable {
public:
	static const QString TABLENAME;
	enum column { ContributionId, MemberId, Fee, Donation, Debit, ValidFrom, Info };
};



class MemberTable {
public:
	static const QString TABLENAME;
	enum column { MemberId, Deleted, FirstName, Name, NickName, FOO_ClubAdress,
		FOO_intern, FOO_CCC, FOO_Shell, FOO_Einzug, FOO_ChaosNr, EntryDate, Info };
};



class RessourcenTable {
public:
	static const QString TABLENAME;
	enum column { RessoucenId, MemberId, EmailAdress, FOO_KeyName, FOO_PublicKey };
};



class BankAccountTable {
public:
	static const QString TABLENAME;
	enum column { BankAccountId, MemberId, AccountNr, BankName, Code };
};
}

#endif /* DATABASESTRUCTURE_H_ */
