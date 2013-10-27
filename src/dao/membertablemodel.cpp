#include "membertablemodel.h"

#include <QSqlRecord>

#include <QDjango.h>
#include <QDjangoQuerySet.h>
#include <QDjangoWhere.h>

namespace membermanager {
namespace dao {

QSqlTableModel *MemberTableModel::createModel(entity::Member::State state, const QVariant& column, const Qt::SortOrder& order)
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("member");
    selectState(model, state, column, order);
    return model;
}

QVariant MemberTableModel::giveMemberIdByRow(QSqlTableModel *model, int row)
{
    QSqlRecord recordLine = model->record(row);
    return recordLine.value("memberId");
}

entity::Member *MemberTableModel::findByMemberId(QVariant id)
{
    return QDjangoQuerySet<entity::Member>()
            .get(QDjangoWhere("memberId", QDjangoWhere::Equals, id));
}

void MemberTableModel::selectState(QSqlTableModel *model, entity::Member::State state, const QVariant& column, const Qt::SortOrder& order)
{
    QString whereClause = QString("%1 = '%2'").arg("state").arg(QChar(static_cast<char>(state)));
    QString orderBy = QString("order by %1 ").arg(column.toString());
    if(order == Qt::SortOrder::DescendingOrder) {
        orderBy.append("desc");
    } else {
        orderBy.append("asc");
    }

    model->setFilter(QString("%1 %2").arg(whereClause).arg(orderBy));
    model->select();

    while(model->canFetchMore())
        model->fetchMore();
}

QList<entity::Member *> MemberTableModel::findByState(entity::Member::State state)
{
    QVariant value(QChar(static_cast<char>(state)));
    QDjangoQuerySet<entity::Member> result = QDjangoQuerySet<entity::Member>()
            .filter(QDjangoWhere("state", QDjangoWhere::Equals, value));

    QList<entity::Member *> list;
    for(int i = 0; result.size() > i; ++i) {
        entity::Member *member = new entity::Member();
        result.at(i, member);
        list.append(member);
    }
    return list;
}


} // namespace dao
} // namespace membermanager
