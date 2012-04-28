#ifndef MEMBERDAO_H
#define MEMBERDAO_H

#include <QObject>
#include <QtSql>

#include "member.h"

namespace membermanager
{
class Member;

namespace model
{

class MemberDao
{
public:
    MemberDao(const QSqlDatabase &aDatabase);
    virtual ~MemberDao() {}

    bool saveRecord(const Member &aMember);

    int newMember();
    void deleteMember(int aMemberId);
    QSqlRecord getRecordWithMemberId(const QString &aTableName, int aMemberId,
                                     int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);
    bool saveNewRecordWithMemberId(const QString &aTableName, int aMemberId, const QSqlRecord &aRecord,
                                   int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);


private:
    QObject *object;
    QSqlDatabase database;
    const QString pkey;
    void rollback(const QSqlQuery &aQuery);
    void printSqlError(const QSqlError &anError);
    void selectTableModel(QSqlTableModel &aModel, const QString &aTableName, int aMemberId,
                          int aSortColumn = -1, Qt::SortOrder aSortOrder = Qt::DescendingOrder);
    bool saveRecordWithMemberId(const QString &aTableName, int aMemberId, const QSqlRecord &aRecord);
};

}
}

#endif // MEMBERDAO_H
