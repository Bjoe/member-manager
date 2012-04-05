#ifndef CONTRIBUTIONMODEL_H
#define CONTRIBUTIONMODEL_H

#include <QtCore>
#include <QtSql>
#include <QTableView>
#include <QModelIndex>

#include "model/memberfilter.h"

namespace membermanager
{
namespace model
{
/// \todo Refactor to ContributionDao
class ContributionModel
{
public:
    ContributionModel(int aMemberId, const QSqlDatabase &aDb = QSqlDatabase::database(), QObject *aParent = 0);
    virtual ~ContributionModel();

    QSqlTableModel *getModel();
    int getMemberId() const;

    QModelIndex insertNewRow();
    bool deleteRow(const QModelIndex &anIndex);

private:
    int memberId;
    QSqlTableModel *model;
};

}
}

#endif // CONTRIBUTIONMODEL_H
