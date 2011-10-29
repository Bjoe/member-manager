#include "memberfactory.h"

#include <QSqlDatabase>
#include "model/memberdao.h"

namespace membermanager
{

Member MemberFactory::createNewMember()
{
    model::MemberDao dao(QSqlDatabase::database());
    int id = dao.newMember();

    return createMember(id);
}

Member MemberFactory::createMember(int anId)
{
    Member member(anId);
    return member;
}

MemberFactory::MemberFactory()
{
}

}
