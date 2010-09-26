/*
 * DatabaseStructure.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: joerg
 */
#include "DatabaseStructure.h"

namespace ClubFrontend
{

const QString AddressTable::TABLENAME = "adresse";

const QString ContributionTable::TABLENAME = "beitragstab";
const QStringList ContributionTable::COLUMNNAME = QStringList()
		<< "beitragstab_pkey" << "dorfmitglied_pkey" << "beitrag"
		<< "spende" << "schulden" << "gueltigab" << "info";

const QString MemberTable::TABLENAME = "dorfmitglied";
const QStringList MemberTable::COLUMNNAME = QStringList()
		<< "dorfmitglied_pkey" << "deleted" << "vorname" << "name"
		<< "nickname";

const QString RessourcenTable::TABLENAME = "kommunikation";

const QString BankAccountTable::TABLENAME = "kontodaten";

}
