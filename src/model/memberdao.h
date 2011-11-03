#ifndef MEMBERDAO_H
#define MEMBERDAO_H

#include <QObject>
#include <QtSql>
#include "model/databasestructure.h"

namespace membermanager
{
namespace model
{

class MemberDao
{
public:
    MemberDao(const QSqlDatabase &aDatabase);
    virtual ~MemberDao() {}

    int newMember();
    void deleteMember(int anId);
    QSqlRecord getRecordWithMemberId(const QString &aTableName, int anId,
                                     int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);
    bool saveRecordWithMemberId(const QString &aTableName, const QSqlRecord &aRecord,
                                int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);
    bool saveNewRecordWithMemberId(const QString &aTableName, const QSqlRecord &aRecord,
                                   int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);


private:
    QObject *object;
    QSqlDatabase database;
    const QString pkey;
    void rollback(const QSqlQuery &aQuery);
    void printSqlError(const QSqlError &anError);
    void selectTableModel(QSqlTableModel &aModel, const QString &aTableName, int anId,
                          int aSortColumn, Qt::SortOrder aSortOrder);
};

}
}

#endif // MEMBERDAO_H
