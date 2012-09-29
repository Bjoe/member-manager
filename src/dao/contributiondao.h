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

    bool saveRecord(const accounting::ContributionEntry &anEntry) const;
    accounting::ContributionEntry findByMemberIdWithPointInTime(int aMemberId, const QDate &aDate) const;
    accounting::ContributionEntry findLastEntryByMemberId(int aMemberId) const;

    QSqlTableModel *getModelByMemberId(int aMemberId) const;
    QModelIndex insertNewEmptyRowWithMemberId(int aMemberId) const;
    bool deleteRow(const QModelIndex &anIndex) const;

private:
    QSqlTableModel *model;

    void printSqlError(const QSqlError &anError) const;
};

} // namespace model
} // namespace membermanager

#endif // MEMBERMANAGER_DAO_CONTRIBUTIONDAO_H
