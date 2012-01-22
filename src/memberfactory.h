#ifndef MEMBERFACTORY_H
#define MEMBERFACTORY_H

#include <QList>
#include <QSqlTableModel>

#include "member.h"

namespace membermanager
{

class MemberFactory
{

public:
    static QList<Member> createMemberList(const QSqlTableModel *aTableModel);
    static Member createNewMember();
    static Member createMember(int anId);

private:
    MemberFactory();
};

}

#endif // MEMBERFACTORY_H
