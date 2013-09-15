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
#include "dao/balancetablemodel.h"

namespace membermanager {
namespace gui {

MemberHandler::MemberHandler(QObject *parent)
    : QObject(parent),
      m_memberState(entity::Member::State::active),
      m_member(new entity::Member()),
      m_bankaccount(new entity::BankAccount()),
      m_contribution(new entity::Contribution()),
      m_memberProxyTableModel(nullptr),
      m_contributionProxyTableModel(new ProxyTableModel()),
      m_balanceProxyTableModel(new ProxyTableModel())
{
    createMemberProxyTableModel();
}

ProxyTableModel *MemberHandler::memberProxyModel() const
{
    return m_memberProxyTableModel;
}

ProxyTableModel *MemberHandler::contributionProxyModel() const
{
    return m_contributionProxyTableModel;
}

ProxyTableModel *MemberHandler::balanceProxyModel() const
{
    return m_balanceProxyTableModel;
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

    QSqlTableModel *model = m_memberProxyTableModel->getModel();
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
    delete m_memberProxyTableModel; // TODO Refactor to autoptr
    createMemberProxyTableModel();
    emit memberProxyModelChanged();
}

void MemberHandler::onMemberSelected(int row)
{
    delete m_member;
    delete m_bankaccount;
    delete m_contribution;

    delete m_contributionProxyTableModel;
    delete m_balanceProxyTableModel;

    QSqlTableModel *memberModel = m_memberProxyTableModel->getModel();
    QVariant memberId = dao::MemberTableModel::giveMemberIdByRow(memberModel, row);
    m_member = dao::MemberTableModel::findByMemberId(memberId);
    m_bankaccount = dao::BankAccountTableModel::findByMemberId(memberId);
    m_contribution = dao::ContributionTableModel::findByMemberId(memberId);

    QSqlTableModel *contributionModel = dao::ContributionTableModel::createModel(memberId);
    m_contributionProxyTableModel = new ProxyTableModel(contributionModel, this);

    QSqlTableModel *balanceModel = dao::BalanceTableModel::createModel(memberId);
    m_balanceProxyTableModel = new ProxyTableModel(balanceModel, this);

    qDebug() << QString("Selected member id: %1").arg(memberId.toString());

    emit memberChanged();
}

void MemberHandler::createMemberProxyTableModel()
{
    QSqlTableModel *model = dao::MemberTableModel::createModel(m_memberState);
    m_memberProxyTableModel = new ProxyTableModel(model, this);
    qDebug() << QString("Database ready. Selected row count: %1").arg(m_memberProxyTableModel->rowCount());
}

} // namespace gui
} // namespace membermanager
