#ifndef TABLEDAO_H
#define TABLEDAO_H

#include <QtSql>

namespace membermanager
{
namespace model
{
class TableDao
{
public:
    int insertNewRow(QSqlTableModel *aModel, int aColumn, const QVariant &aValue);

};

}
}

#endif // TABLEDAO_H
