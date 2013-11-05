#include "balancetablemodel.h"

#include <QString>
#include <QSqlRecord>

#include "QDjango.h"
#include "QDjangoQuerySet.h"
#include "QDjangoWhere.h"

namespace membermanager {
namespace dao {

QSqlTableModel *BalanceTableModel::createModel(const QVariant &memberId)
{
    QString whereClause = QString("%1 = %2").arg("memberId").arg(memberId.toString());

    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("Balance");
    model->setFilter(whereClause);
    model->setSort(3, Qt::DescendingOrder);
    model->select();

    while(model->canFetchMore())
        model->fetchMore();

    return model;
}

entity::Balance *BalanceTableModel::giveBalanceByRow(const QSqlTableModel *model, int row)
{
    QSqlRecord recordLine = model->record(row);
    QVariant id = recordLine.value("balanceId");

    return QDjangoQuerySet<entity::Balance>().get(QDjangoWhere("balanceId", QDjangoWhere::Equals, id));
}

QList<QObject *> BalanceTableModel::findContributionByMemberIdAndYear(const QVariant &memberId, const QVariant &year)
{
    QDjangoQuerySet<entity::Balance> result = QDjangoQuerySet<entity::Balance>()
            .filter(QDjangoWhere("memberId", QDjangoWhere::Equals, memberId) &&
                    (QDjangoWhere("account", QDjangoWhere::Equals, "11") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "12")))
            .orderBy(QStringList() << "valuta");

    QList<QObject *> list;
    for(int i = 0; i < result.size(); ++i) {
        entity::Balance *balance = new entity::Balance();
        result.at(i, balance);
        if(balance->valuta().year() == year) // TODO In SQL
            list.append(balance);
        else
            delete balance;
    }
    return list;
}

double BalanceTableModel::calculateFeeSumByMemberId(const QVariant& memberId)
{
    QDjangoQuerySet<entity::Balance> result = QDjangoQuerySet<entity::Balance>()
            .filter(QDjangoWhere("memberId", QDjangoWhere::Equals, memberId) &&
                    (QDjangoWhere("account", QDjangoWhere::Equals, "11") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "-11") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "4") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "-4") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "3") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "-3") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "2") ||
                     QDjangoWhere("account", QDjangoWhere::Equals, "-2")));

    double sum = 0.0;
    for(const entity::Balance &balance : result) {
        sum += balance.value();
    }
    return sum;
}

} // namespace dao
} // namespace membermanager
