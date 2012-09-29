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

    Member findByMemberId(int aMemberId) const;
    QList<Member> findByDeleted(bool isDeleted) const;

    QSqlTableModel *modelSelectDeleted(bool isDeleted) const;

    bool saveRecord(const Member &aMember);

    int createMember();
    void deleteMember(int aMemberId);

private:
    QSqlDatabase database;
    QObject *parent;

    QSqlTableModel *createMemberModel() const;
    QSqlTableModel *createBankModel() const;
    QSqlTableModel *createAddressModel() const;
    QSqlTableModel *createResourceModel() const;

    void rollback(const QSqlQuery &aQuery);
    void printSqlError(const QSqlError &anError) const;
    void selectDeleted(QSqlTableModel *aModel, bool isDeleted) const;
    void selectTableModel(QSqlTableModel *aModel, const QString &aColumnnameId, int aMemberId) const;
    bool saveRecordOnModel(QSqlTableModel *aTableModel, const QSqlRecord &aRecord);
    QSqlRecord record(const QSqlTableModel *aTableModel) const;
};

}
}

#endif // MEMBERDAO_H
