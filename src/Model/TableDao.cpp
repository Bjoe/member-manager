#include "TableDao.h"


namespace ClubFrontend
{
namespace Model
{

int TableDao::insertNewRow ( QSqlTableModel* aModel,
                             int aColumn, const QVariant& aValue )
{
    QSqlRecord record = aModel->record();
    record.setValue ( aColumn, aValue );
    int row = aModel->rowCount();
    aModel->insertRow ( row );
    aModel->setRecord ( row, record );
    aModel->submitAll();
    return row;
}


}
}
