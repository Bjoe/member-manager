#include "memberfactory.h"

#include <QSqlDatabase>
#include "model/memberfilter.h"
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
    model::MemberFilter filter = model::MemberFilter::build().withMemberId(anId);
    Member member(filter);
    return member;
}

MemberFactory::MemberFactory()
{
}

}
