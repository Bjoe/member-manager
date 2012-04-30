#ifndef MEMBERMANAGER_DAO_CONTRIBUTIONDAO_H
#define MEMBERMANAGER_DAO_CONTRIBUTIONDAO_H

#include <QtSql>
#include <QDate>

#include "accounting/contributionentry.h"

namespace membermanager {
namespace accounting {

class ContributionEntry;

}
namespace dao {

class ContributionDao
{
public:
    ContributionDao(const QSqlDatabase &aDatabase = QSqlDatabase::database(), QObject *aParent = 0);

    bool saveRecord(const accounting::ContributionEntry &anEntry);
    accounting::ContributionEntry findByMemberIdWithPointInTime(int aMemberId, const QDate &aDate);
    accounting::ContributionEntry findLastDateByMemberId(int aMemberId);

    QSqlTableModel *getModelByMemberId(int aMemberId);
    QModelIndex insertNewEmptyRowWithMemberId(int aMemberId);
    bool deleteRow(const QModelIndex &anIndex);

private:
    QSqlTableModel *model;

    void printSqlError(const QSqlError &anError);
};

} // namespace model
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CONTRIBUTIONDAO_H
