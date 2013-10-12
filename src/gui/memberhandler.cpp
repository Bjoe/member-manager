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
      m_member(new entity::Member()),
      m_bankaccount(new entity::BankAccount()),
      m_contribution(new entity::Contribution()),
      m_contributionProxyTableModel(new ProxyTableModel()),
      m_balanceProxyTableModel(new ProxyTableModel())
{}

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

void MemberHandler::onSelectedMemberId(QVariant id)
{
    delete m_member;
    delete m_bankaccount;
    delete m_contribution;

    delete m_contributionProxyTableModel;
    delete m_balanceProxyTableModel;

    m_member = dao::MemberTableModel::findByMemberId(id);
    m_bankaccount = dao::BankAccountTableModel::findByMemberId(id);
    m_contribution = dao::ContributionTableModel::findLastEntryByMemberId(id);

    QSqlTableModel *contributionModel = dao::ContributionTableModel::createModel(id);
    m_contributionProxyTableModel = new ProxyTableModel(contributionModel, this);

    QSqlTableModel *balanceModel = dao::BalanceTableModel::createModel(id);
    m_balanceProxyTableModel = new ProxyTableModel(balanceModel, this);

    qDebug() << QString("Selected member id: %1").arg(m_member->memberId());

    emit memberChanged();
}

void MemberHandler::onNewMember()
{
    delete m_member;
    delete m_bankaccount;
    delete m_contribution;

    delete m_contributionProxyTableModel;
    delete m_balanceProxyTableModel;

    m_member = new entity::Member();
    m_bankaccount = new entity::BankAccount();
    m_contribution = new entity::Contribution();

    m_contributionProxyTableModel = new ProxyTableModel(this);
    m_balanceProxyTableModel = new ProxyTableModel(this);

    emit memberChanged();
}

} // namespace gui
} // namespace membermanager
