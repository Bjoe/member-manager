#ifndef MEMBERMODEL_H_
#define MEMBERMODEL_H_

#include <QtCore>
#include <QtSql>
#include <QTableView>

#include "member.h"

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

    int getMemberId ( const QModelIndex& anIndex ) const;

    QString getLastError() const;
    void initTableView ( QTableView* aTableView ) const;

private:
    QSqlTableModel* const model;
};

}
}

#endif /* MEMBERMODEL_H_ */
