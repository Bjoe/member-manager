#ifndef MEMBERMODEL_H_
#define MEMBERMODEL_H_

#include <QtCore>
#include <QtSql>
#include <QTableView>

#include "Model/Member.h"

namespace ClubFrontend
{
namespace Model
{
  
class MemberModel: public QObject
{

public:
    MemberModel ( const QSqlDatabase& aDb );
    virtual ~MemberModel();

    void setFilter ( const QString aSqlFilter );
    void refresh();

    int getMemberId ( const QModelIndex& anIndex );
    QVector< Member > * getSelectedMembers();

    QString getLastError() const;
    void initTableView ( QTableView* aTableView ) const;

private:
    QSqlTableModel* const model;
};

}
}

#endif /* MEMBERMODEL_H_ */
