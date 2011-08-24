#include "model/saldosummodel.h"

#include "model/databasestructure.h"

namespace ClubFrontend
{
namespace Model
{

SaldoSumModel::SaldoSumModel ( const QSqlDatabase & aDb )
        : model ( new QSqlQueryModel ( this ) )
{
    QString query = QString ( "select sum(a.%1), b.%2, b.%3, b.%4, c.%5 "
                              "from %6 a, %7 b, %8 c "
                              "where a.%9=b.%10 "
                              "and c.%11=b.%10 "
                              "and b.%12='%13' "
                              "group by b.%2, b.%3, b.%4, c.%5" )
                    .arg ( SaldoTable::COLUMNNAME[SaldoTable::betrag] )
                    .arg ( MemberTable::COLUMNNAME[MemberTable::NickName] )
                    .arg ( MemberTable::COLUMNNAME[MemberTable::FirstName] )
                    .arg ( MemberTable::COLUMNNAME[MemberTable::Name] )
                    .arg ( RessourcenTable::COLUMNNAME[RessourcenTable::EmailAdress] )
                    .arg ( SaldoTable::TABLENAME )
                    .arg ( MemberTable::TABLENAME )
                    .arg ( RessourcenTable::TABLENAME )
                    .arg ( SaldoTable::COLUMNNAME[SaldoTable::dorfmitglied_pkey] )
                    .arg ( MemberTable::COLUMNNAME[MemberTable::MemberId] )
                    .arg ( RessourcenTable::COLUMNNAME[RessourcenTable::MemberId] )
                    .arg ( MemberTable::COLUMNNAME[MemberTable::Deleted] )
                    .arg ( QString ( "false" ) );
    model->setQuery ( query, aDb );
}

void SaldoSumModel::initTableView ( QTableView* const aView )
{
    aView->setModel ( model );
    aView->setColumnHidden ( 5, true );
}

}
}
