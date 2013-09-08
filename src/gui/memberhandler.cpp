#include "memberhandler.h"

#include <QDebug>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlTableModel>

#include <QDjango.h>
#include <QDjangoQuerySet.h>
#include <QDjangoWhere.h>

#include "dao/membertablemodel.h"
#include "dao/bankaccounttablemodel.h"
#include "dao/contributiontablemodel.h"

namespace membermanager {
namespace gui {

MemberHandler::MemberHandler(QObject *parent)
    : QObject(parent),
      m_memberState(entity::Member::State::active),
      m_member(new entity::Member()),
      m_bankaccount(new entity::BankAccount()),
      m_contribution(new entity::Contribution()),
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

entity::BankAccount *MemberHandler::bankAccount() const
{
    return m_bankaccount;
}

entity::Contribution *MemberHandler::contribution() const
{
    return m_contribution;
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
    delete m_member;
    delete m_bankaccount;
    delete m_contribution;

    QSqlTableModel *model = m_proxyTableModel->getModel();
    QVariant memberId = dao::MemberTableModel::giveMemberIdByRow(model, row);
    m_member = dao::MemberTableModel::findByMemberId(memberId);
    m_bankaccount = dao::BankAccountTableModel::findByMemberId(memberId);
    m_contribution = dao::ContributionTableModel::findByMemberId(memberId);

    qDebug() << QString("Selected member id: %1").arg(memberId.toString());

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
