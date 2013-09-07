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
      m_proxyTableModel(nullptr)
{
    createProxyTableModel();
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

bool MemberHandler::isInactive() const
{
    if(m_memberState == entity::Member::State::inactive) {
        return true;
    } else {
        return false;
    }
}

void MemberHandler::setAndSelectInactiveMember(bool deleted)
{
    entity::Member::State memberState = entity::Member::State::active;
    if(deleted) {
        memberState = entity::Member::State::inactive;
    }
    selectMemberState(memberState);
}

void MemberHandler::onDatabaseReady()
{
    delete m_proxyTableModel; // TODO Refactor to autoptr
    createProxyTableModel();
    emit proxyModelChanged();
}

void MemberHandler::onMemberSelected(int row)
{
    QSqlTableModel *model = m_proxyTableModel->getModel();
    m_member = dao::MemberTableModel::findMemberByRow(model, row);

    qDebug() << QString("Selected member id: %1").arg(m_member->memberId());

    emit memberChanged();
}

void MemberHandler::createProxyTableModel()
{
    QSqlTableModel *model = dao::MemberTableModel::createModel(m_memberState);
    m_proxyTableModel = new ProxyTableModel(model, this);
    qDebug() << QString("Database ready. Selected row count: %1").arg(m_proxyTableModel->rowCount());
}

} // namespace gui
} // namespace membermanager
