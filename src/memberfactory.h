#ifndef MEMBERFACTORY_H
#define MEMBERFACTORY_H

#include "member.h"

namespace membermanager
{

class MemberFactory
{

public:
    static Member createNewMember();
    static Member createMember(int anId);

private:
    MemberFactory();
};

}

#endif // MEMBERFACTORY_H
