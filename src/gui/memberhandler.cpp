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
      m_memberState(entity::Member::State::active),
      m_member(new entity::Member()),
      m_proxyTableModel(new ProxyTableModel())
{
}

ProxyTableModel *MemberHandler::proxyModel() const
{
    return m_proxyTableModel;
}

entity::Member *MemberHandler::member() const
{
    return m_member;
}

entity::Member::State MemberHandler::memberState() const
{
    return m_memberState;
}

void MemberHandler::selectMemberState(entity::Member::State state)
{
    m_memberState = state;

    QSqlTableModel *model = m_proxyTableModel->getModel();
    dao::MemberTableModel::selectState(model, m_memberState);

    emit memberStateChanged();
}

void MemberHandler::onDatabaseReady()
{
    QSqlTableModel *model = dao::MemberTableModel::createModel(m_memberState);
    m_proxyTableModel->reload(model);

    qDebug() << QString("Database ready. Selected row count: %1").arg(m_proxyTableModel->rowCount());
    emit proxyModelChanged();
}

void MemberHandler::onMemberSelected(int row)
{
    QSqlTableModel *model = m_proxyTableModel->getModel();
    m_member = dao::MemberTableModel::findMemberByRow(model, row);

    qDebug() << QString("Selected member id: %1").arg(m_member->memberId());

    emit memberChanged();
}



} // namespace gui
} // namespace membermanager
