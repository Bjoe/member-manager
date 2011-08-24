#ifndef MEMBERDAO_H
#define MEMBERDAO_H

#include <QtSql>

namespace ClubFrontend
{
namespace Model
{

class MemberDao
{
public:
    MemberDao(const QSqlDatabase &aDatabase);
    ~MemberDao();

    int newMember();
    void deleteMember(int anId);

private:
    QSqlDatabase database;
    void rollback(const QSqlQuery aQuery);
};

}
}

#endif // MEMBERDAO_H
