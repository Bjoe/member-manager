#include "memberfactory.h"

#include <QSqlDatabase>
#include "model/memberdao.h"
#include "model/databasestructure.h"

namespace membermanager
{

QList<Member> MemberFactory::createMemberList(const QSqlTableModel *aTableModel)
{
    QList<Member> list;
    for(int row = 0; row < aTableModel->rowCount(); row++) {
        QModelIndex index = aTableModel->index(row, model::MemberTable::MemberId);
        QVariant variant = index.data();
        Member member = createMember(variant.toInt());
        list.append(member);
    }
    return list;
}

Member MemberFactory::createNewMember()
{
    model::MemberDao dao(QSqlDatabase::database());
    int id = dao.newMember();

    return dao.findByMemberId(id);
}

/// \todo getMemberById(id)
Member MemberFactory::createMember(int anId)
{
    model::MemberDao memberDao(QSqlDatabase::database());
    return memberDao.findByMemberId(anId);
}

MemberFactory::MemberFactory()
{
}

}
