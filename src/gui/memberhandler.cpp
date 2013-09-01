#include "memberhandler.h"

#include <QDebug>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlTableModel>

#include <QDjango.h>
#include <QDjangoQuerySet.h>
#include <QDjangoWhere.h>

#include "dao/membertablemodel.h"

namespace membermanager {
namespace gui {

MemberHandler::MemberHandler(QObject *parent)
    : QObject(parent),
      m_member(new entity::Member()),
      m_proxyTableModel(new ProxyTableModel())
{
}

ProxyTableModel *MemberHandler::proxyModel()
{
    return m_proxyTableModel;
}

entity::Member *MemberHandler::member()
{
    return m_member;
}

void MemberHandler::onDatabaseReady()
{
    QSqlTableModel *model = dao::MemberTableModel::createModel();
    m_proxyTableModel->reload(model);

    qDebug() << QString("Database ready. Selected row count: %1").arg(m_proxyTableModel->rowCount());
    emit proxyModelChanged();
}

void MemberHandler::onMemberSelected(int row)
{
    QSqlTableModel *model = m_proxyTableModel->getModel();
    QSqlRecord recordLine = model->record(row);
    QVariant variant = recordLine.value("memberId");
    QString memberId = variant.toString();

    QDjangoQuerySet<entity::Member> members;
    QDjangoQuerySet<entity::Member> result = members.filter(QDjangoWhere("memberId", QDjangoWhere::Equals, memberId));

    qDebug() << QString("Selected member id: %1 and found: %2").arg(memberId).arg(result.size());
    result.at(0, m_member);

    emit memberChanged();
}



} // namespace gui
} // namespace membermanager
