#ifndef TABLEDAO_H
#define TABLEDAO_H

#include <QtSql>

namespace ClubFrontend
{
namespace Model
{
class TableDao
{
public:
    int insertNewRow ( QSqlTableModel* aModel, int aColumn, const QVariant& aValue );

};

}
}

#endif // TABLEDAO_H
