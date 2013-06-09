#ifndef DATABASESTRUCTURE_H_
#define DATABASESTRUCTURE_H_

#include <QString>
#include <QStringList>

namespace membermanager
{
namespace dao
{

class AddressTable
{
public:
    static const QString TABLENAME;
    enum column {
        AddressId, MemberId, Street, ZipCode, Town
    };
    static const QStringList COLUMNNAME;
};

class ContributionTable
{
public:
    static const QString TABLENAME;
    enum column {
        ContributionId, MemberId, Fee, Donation, AdditionalFee, ValidFrom, Info
    };
    static const QStringList COLUMNNAME;
};

class MemberTable
{
public:
    static const QString TABLENAME;
    enum column {
        MemberId,
        Deleted,
        FirstName,
        Name,
        NickName,
        FOO_ClubAdress,
        FOO_intern,
        FOO_CCC,
        FOO_Shell,
        FOO_Einzug,
        FOO_ChaosNr,
        EntryDate,
        Info
    };
    static const QStringList COLUMNNAME;
};

class RessourcenTable
{
public:
    static const QString TABLENAME;
    enum column {
        RessoucenId, MemberId, EmailAdress, FOO_KeyName, FOO_PublicKey
    };
    static const QStringList COLUMNNAME;
};

class BankAccountTable
{
public:
    static const QString TABLENAME;
    enum column {
        BankAccountId, MemberId, AccountNr, BankName, Code
    };
    static const QStringList COLUMNNAME;
};

class CashTable
{
public:
    static const QString TABLENAME;
    enum column {
        kasse_pkey,
        deleted,
        einlesedatum,
        einleseid,
        auszug,
        zwshkenn60,
        zwbudatum60,
        zwischensaldo60,
        zwshkenn62,
        zwbudatum62,
        zwischensaldo62,
        valutadatum,
        buchungsdatum,
        shkenn,
        betrag,
        buschl,
        bankbuschl,
        fremdblz,
        fremdktnr,
        fremdname,
        bezeichnung,
        barkonto,
        konten,
        dorfmitglied_pkey,
        erfasst
    };
    static const QStringList COLUMNNAME;
};

class BalanceTable
{
public:
    static const QString TABLENAME;
    enum column {
        saldo_pkey,
        dorfmitglied_pkey,
        betrag,
        datum,
        bezeichnung,
        barkonto,
        konten,
        kasse_pkey,
        info
    };
    static const QStringList COLUMNNAME;
};

}
}

#endif /* DATABASESTRUCTURE_H_ */
