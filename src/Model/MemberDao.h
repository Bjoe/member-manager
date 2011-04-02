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
    void deleteMember(int anId);
};

}
}

#endif // MEMBERDAO_H
