#ifndef CONTRIBUTIONMODEL_H
#define CONTRIBUTIONMODEL_H

#include <QtCore>
#include <QtSql>
#include <QTableView>

namespace membermanager
{
namespace model
{

class ContributionModel : public QObject
{
public:
    ContributionModel(const QSqlDatabase &aDb);
    virtual ~ContributionModel();

    void selectMemberId(const int aMemberId);

    void initTableView(QTableView *aTableView) const;

private:
    QSqlTableModel *model;
};

}
}

#endif // CONTRIBUTIONMODEL_H
