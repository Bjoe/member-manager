#ifndef MEMBERDAO_H
#define MEMBERDAO_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtSql>

#include "member.h"

namespace membermanager
{
class Member;

namespace dao
{

class MemberDao
{
public:
    MemberDao(const QSqlDatabase &aDatabase = QSqlDatabase::database(), QObject *aParent = 0);

    Member findByMemberId(int aMemberId);
    QList<Member> findByDeleted(bool isDeleted);

    QSqlTableModel *modelSelectDeleted(bool isDeleted);

    bool saveRecord(const Member &aMember);

    int createMember();
    void deleteMember(int aMemberId);

private:
    QSqlDatabase database;
    QObject *parent;

    QSqlTableModel *createMemberModel();
    QSqlTableModel *createBankModel();
    QSqlTableModel *createAddressModel();
    QSqlTableModel *createResourceModel();

    void rollback(const QSqlQuery &aQuery);
    void printSqlError(const QSqlError &anError);
    void selectDeleted(QSqlTableModel *aModel, bool isDeleted);
    void selectTableModel(QSqlTableModel *aModel, const QString &aColumnnameId, int aMemberId);
    bool saveRecordOnModel(QSqlTableModel *aTableModel, const QSqlRecord &aRecord);
    QSqlRecord record(const QSqlTableModel *aTableModel);
};

}
}

#endif // MEMBERDAO_H
