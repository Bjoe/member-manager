#ifndef MEMBERMANAGER_MODEL_CONTRIBUTIONDAO_H
#define MEMBERMANAGER_MODEL_CONTRIBUTIONDAO_H

#include <QtSql>

#include "accounting/contributionentry.h"

namespace membermanager {
namespace accounting {

class ContributionEntry;

}
namespace model {

class ContributionDao
{
public:
    ContributionDao(const QSqlDatabase &aDatabase);

    bool saveRecord(const accounting::ContributionEntry &anEntry);

private:
    QSqlDatabase database;

    void printSqlError(const QSqlError &anError);
};

} // namespace model
} // namespace membermanager

#endif // MEMBERMANAGER_MODEL_CONTRIBUTIONDAO_H
