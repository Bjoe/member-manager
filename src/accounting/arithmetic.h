#ifndef MEMBERMANAGER_ACCOUNTING_ARITHMETIC_H
#define MEMBERMANAGER_ACCOUNTING_ARITHMETIC_H

#include "entity/contribution.h"

namespace membermanager {
namespace accounting {

class Arithmetic
{
public:
    Arithmetic();
    virtual ~Arithmetic();

    virtual void calculate(const entity::Contribution *contribution);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_ARITHMETIC_H
