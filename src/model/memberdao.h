#ifndef MEMBERDAO_H
#define MEMBERDAO_H

#include <QObject>
#include <QtSql>
#include "model/memberfilter.h"

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
    void deleteMember(const MemberFilter &aFilter);
    QSqlRecord getRecordWithMemberId(const QString &aTableName, const MemberFilter &aFilter,
                                     int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);
    bool saveRecordWithMemberId(const QString &aTableName, const MemberFilter &aFilter, const QSqlRecord &aRecord,
                                int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);
    bool saveNewRecordWithMemberId(const QString &aTableName, const MemberFilter &aFilter, const QSqlRecord &aRecord,
                                   int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);


private:
    QObject *object;
    QSqlDatabase database;
    const QString pkey;
    void rollback(const QSqlQuery &aQuery);
    void printSqlError(const QSqlError &anError);
    void selectTableModel(QSqlTableModel &aModel, const QString &aTableName, const MemberFilter &aFilter,
                          int aSortColumn, Qt::SortOrder aSortOrder);
};

}
}

#endif // MEMBERDAO_H
