#include "membertablemodel.h"

#include <QVariant>
#include <QSqlRecord>
#include <QSqlTableModel>

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

entity::Member *MemberTableModel::findMemberByRow(QSqlTableModel *model, int row)
{
    QSqlRecord recordLine = model->record(row);
    QVariant memberId = recordLine.value("memberId");

    QDjangoQuerySet<entity::Member> members;
    QDjangoQuerySet<entity::Member> result = members.filter(QDjangoWhere("memberId", QDjangoWhere::Equals, memberId));

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


} // namespace dao
} // namespace membermanager
