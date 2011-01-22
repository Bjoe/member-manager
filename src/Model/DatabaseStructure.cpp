/*
 * DatabaseStructure.cpp
 *
 *  Created on: Jul 23, 2010
 *      Author: joerg
 */
#include "Model/DatabaseStructure.h"

namespace ClubFrontend
{

const QString AddressTable::TABLENAME = "adresse";

const QString ContributionTable::TABLENAME = "beitragstab";
const QStringList ContributionTable::COLUMNNAME = QStringList()
		<< "beitragstab_pkey" << "dorfmitglied_pkey" << "beitrag" << "spende"
		<< "schulden" << "gueltigab" << "info";

const QString MemberTable::TABLENAME = "dorfmitglied";
const QStringList MemberTable::COLUMNNAME = QStringList()
		<< "dorfmitglied_pkey" << "deleted" << "vorname" << "name"
		<< "nickname";

const QString RessourcenTable::TABLENAME = "kommunikation";
const QStringList RessourcenTable::COLUMNNAME = QStringList() 
		<< "kommunikation_pkey" << "dorfmitglied_pkey" << "email";

const QString BankAccountTable::TABLENAME = "kontodaten";

const QString KassaTable::TABLENAME = "kasse";
const QStringList KassaTable::COLUMNNAME = QStringList() << "kasse_pkey"
		<< "deleted" << "einlesedatum" << "einleseid" << "auszug"
		<< "zwshkenn60" << "zwbudatum60" << "zwischensaldo60" << "zwshkenn62"
		<< "zwbudatum62" << "zwischensaldo62" << "valutadatum"
		<< "buchungsdatum" << "shkenn" << "betrag" << "buschl" << "bankbuschl"
		<< "fremdblz" << "fremdktnr" << "fremdname" << "bezeichnung"
		<< "barkonto" << "konten" << "dorfmitglied_pkey" << "erfasst";

const QString SaldoTable::TABLENAME = "saldo";
const QStringList SaldoTable::COLUMNNAME = QStringList() << "saldo_pkey"
		<< "dorfmitglied_pkey" << "betrag" << "datum" << "bezeichnung"
		<< "barkonto" << "konten" << "kasse_pkey" << "info";
}
