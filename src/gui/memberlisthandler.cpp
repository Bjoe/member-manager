#include "memberlisthandler.h"

#include <QDebug>
#include <QVariant>
#include <QSqlTableModel>

#include "dao/membertablemodel.h"

namespace membermanager {
namespace gui {

MemberListHandler::MemberListHandler(QObject *parent) :
    QObject(parent),
    m_memberState(entity::Member::State::active),
    m_memberProxyTableModel(nullptr)
{
    createMemberProxyTableModel();
}

ProxyTableModel *MemberListHandler::memberProxyModel() const
{
    return m_memberProxyTableModel;
}

entity::Member::State MemberListHandler::memberState() const
{
    return m_memberState;
}

void MemberListHandler::setMemberState(entity::Member::State state)
{
    m_memberState = state;
    emit memberStateChanged();
}

bool MemberListHandler::isInactive() const
{
    if(m_memberState == entity::Member::State::inactive) {
        return true;
    } else {
        return false;
    }
}

void MemberListHandler::setBoolMemberState(bool isInactive)
{
    m_memberState = entity::Member::State::active;
    if(isInactive) {
        m_memberState = entity::Member::State::inactive;
    }
    emit memberStateChanged();
}

void MemberListHandler::onRefresh(const QVariant &column, const Qt::SortOrder order)
{
    delete m_memberProxyTableModel; // TODO Refactor to autoptr
    createMemberProxyTableModel(column, order);
    emit memberProxyModelChanged();
}

void MemberListHandler::onSelectedRow(int row)
{
    QSqlTableModel *memberModel = m_memberProxyTableModel->getModel();
    QVariant memberId = dao::MemberTableModel::giveMemberIdByRow(memberModel, row);
    emit selectMemberId(memberId);
}

void MemberListHandler::createMemberProxyTableModel(const QVariant &column, const Qt::SortOrder order)
{
    QSqlTableModel *model = dao::MemberTableModel::createModel(m_memberState, column, order);
    m_memberProxyTableModel = new ProxyTableModel(model, this);
    qDebug() << QString("Database ready. Selected row count: %1").arg(m_memberProxyTableModel->rowCount());
}

} // namespace gui
} // namespace membermanager
