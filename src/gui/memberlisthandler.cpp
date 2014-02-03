#include "memberlisthandler.h"

#include <QDebug>
#include <QVariant>
#include <QSqlTableModel>

#include "dao/membertablemodel.h"

namespace membermanager {
namespace gui {

MemberListHandler::MemberListHandler(QObject *parent) :
    QObject(parent)
{
    refresh();
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

void MemberListHandler::reset()
{
    delete m_memberProxyTableModel->getModel(); // TODO Add SharedPointer!
    delete m_memberProxyTableModel;
    m_memberProxyTableModel = new ProxyTableModel(this);
    refresh();
    emit memberProxyModelChanged();
}

void MemberListHandler::refresh(const QVariant &column, const Qt::SortOrder order)
{
    QSqlTableModel *model = dao::MemberTableModel::createModel(m_memberState, column, order);
    m_memberProxyTableModel->setModel(model);
    qDebug() << QString("Refresh: Selected row count: %1").arg(m_memberProxyTableModel->rowCount());
}

void MemberListHandler::selectedRow(int row)
{
    QSqlTableModel *memberModel = m_memberProxyTableModel->getModel();
    QVariant memberId = dao::MemberTableModel::giveMemberIdByRow(memberModel, row);
    emit selectMemberId(memberId);
}

} // namespace gui
} // namespace membermanager
