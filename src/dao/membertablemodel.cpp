#include "membertablemodel.h"

#include <QSqlRecord>

#include <QDjango.h>
#include <QDjangoQuerySet.h>
#include <QDjangoWhere.h>

namespace membermanager {
namespace dao {

QSqlTableModel *MemberTableModel::createModel(entity::Member::State state)
{
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("member");
    selectState(model, state);
    return model;
}

QVariant MemberTableModel::giveMemberIdByRow(QSqlTableModel *model, int row)
{
    QSqlRecord recordLine = model->record(row);
    return recordLine.value("memberId");
}

entity::Member *MemberTableModel::findByMemberId(QVariant id)
{
    QDjangoQuerySet<entity::Member> members;
    QDjangoQuerySet<entity::Member> result = members.filter(QDjangoWhere("memberId", QDjangoWhere::Equals, id));

    entity::Member *member = new entity::Member();
    result.at(0, member);
    return member;
}

void MemberTableModel::selectState(QSqlTableModel *model, entity::Member::State state)
{
    QString whereClause = QString("%1 = '%2'").arg("state").arg(QChar(static_cast<char>(state)));
    model->setFilter(whereClause);
    model->select();
}

QList<entity::Member *> MemberTableModel::findByState(entity::Member::State state)
{
    QVariant value(QChar(static_cast<char>(state)));
    QDjangoQuerySet<entity::Member> memberSet;
    QDjangoQuerySet<entity::Member> result = memberSet.filter(QDjangoWhere("state", QDjangoWhere::Equals, value));

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
