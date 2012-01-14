#ifndef MEMBERMODEL_H_
#define MEMBERMODEL_H_

#include <QtCore>
#include <QtSql>
#include <QTableView>

#include "member.h"

namespace membermanager
{
namespace model
{

class MemberModel
{

public:
    MemberModel(QObject *anObject, const QSqlDatabase &aDb);
    virtual ~MemberModel();

    void setFilter(const QString aSqlFilter);
    int getMemberId(const QModelIndex &anIndex) const;
    QSqlTableModel* getModel();

    QString getLastError() const;

private:
    QSqlTableModel *model;
};

}
}

#endif /* MEMBERMODEL_H_ */
