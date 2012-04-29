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

    Member findByMemberId(int aMemberId);

    int newMember();
    void deleteMember(int aMemberId);

private:
    QObject *object;
    QSqlDatabase database;
    const QString pkey;
    void rollback(const QSqlQuery &aQuery);
    void printSqlError(const QSqlError &anError);
    void selectTableModel(QSqlTableModel &aModel, const QString &aTableName, int aMemberId);
    bool saveRecordWithMemberId(const QString &aTableName, int aMemberId, const QSqlRecord &aRecord);
    QSqlRecord getRecordWithMemberId(const QString &aTableName, int aMemberId);
};

}
}

#endif // MEMBERDAO_H
