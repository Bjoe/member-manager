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

class ContributionModel
{
public:
    ContributionModel(const MemberFilter &aFilter, const QSqlDatabase &aDb = QSqlDatabase::database(), QObject *aParent = 0);
    virtual ~ContributionModel();

    void initTableView(QTableView *aTableView) const;

    QString getMemberId() const;

    QModelIndex insertNewRow();
    bool deleteRow(const QModelIndex &anIndex);

private:
    QSqlTableModel *model;
};

}
}

#endif // CONTRIBUTIONMODEL_H
