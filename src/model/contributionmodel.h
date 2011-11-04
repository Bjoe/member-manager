#ifndef CONTRIBUTIONMODEL_H
#define CONTRIBUTIONMODEL_H

#include <QtCore>
#include <QtSql>
#include <QTableView>

#include "model/memberfilter.h"

namespace membermanager
{
namespace model
{

class ContributionModel : public QObject
{
public:
    ContributionModel(const MemberFilter &aFilter, const QSqlDatabase &aDb);
    virtual ~ContributionModel();

    void initTableView(QTableView *aTableView) const;

private:
    QSqlTableModel *model;
};

}
}

#endif // CONTRIBUTIONMODEL_H
