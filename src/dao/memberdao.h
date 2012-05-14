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

    bool saveRecord(const Member &aMember);

    Member findByMemberId(int aMemberId);
    Member findByRow(int aRowNr);
    QList<Member> findByDeleted(bool isDeleted);
    QSqlTableModel *selectDeleted(bool isDeleted);
    QSqlTableModel *model();

    int newMember();
    void deleteMember(int aMemberId);

private:
    QSqlDatabase database;
    QSqlTableModel *memberModel;
    QSqlTableModel *ressourcenModel;
    QSqlTableModel *bankModel;
    QSqlTableModel *addressModel;

    void rollback(const QSqlQuery &aQuery);
    void printSqlError(const QSqlError &anError);
    void selectTableModel(QSqlTableModel *aModel, const QString &aColumnnameId, int aMemberId);
    bool saveRecordOnModel(QSqlTableModel *aTableModel, const QSqlRecord &aRecord);
    QSqlRecord record(const QSqlTableModel *aTableModel);
};

}
}

#endif // MEMBERDAO_H
