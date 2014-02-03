#include "memberhandler.h"

#include <QDebug>
#include <QVariant>
#include <QSqlRecord>
#include <QClipboard>
#include <QApplication>

#include <QDjango.h>
#include <QDjangoQuerySet.h>
#include <QDjangoWhere.h>

#include "dao/membertablemodel.h"
#include "dao/bankaccounttablemodel.h"
#include "dao/sepaaccounttablemodel.h"
#include "dao/contributiontablemodel.h"
#include "dao/balancetablemodel.h"

namespace membermanager {
namespace gui {

MemberHandler::MemberHandler(QObject *parent)
    : QObject(parent)
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
    return m_bankAccount;
}

entity::SepaAccount *MemberHandler::sepaAccount() const
{
    return m_sepaAccount;
}

entity::Contribution *MemberHandler::contribution() const
{
    return m_contribution;
}

void MemberHandler::copyBalanceToClipboard(int row)
{
    const QSqlTableModel* model = m_balanceProxyTableModel->getModel();
    QString text("Valuta\tBetrag\tText\n");
    text.append(createText(model, row));

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void MemberHandler::copyAllBalanceToClipboard()
{
    const QSqlTableModel* model = m_balanceProxyTableModel->getModel();
    QString text("Valuta\tBetrag\tText\n");

    for(int row = 0; model->rowCount() > row; ++row) {
        text.append(createText(model, row));
    }

    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void MemberHandler::reset()
{
    delete m_member;
    delete m_bankAccount;
    delete m_sepaAccount;
    delete m_contribution;
    delete m_contributionProxyTableModel;
    delete m_balanceProxyTableModel;

    m_member = new entity::Member();
    m_bankAccount = new entity::BankAccount();
    m_sepaAccount = new entity::SepaAccount();
    m_contribution = new entity::Contribution();

    m_contributionProxyTableModel = new ProxyTableModel(this);
    m_balanceProxyTableModel = new ProxyTableModel(this);

    emit memberChanged();
}

QString MemberHandler::createText(const QSqlTableModel* model, int row)
{
    entity::Balance* balance = dao::BalanceTableModel::giveBalanceByRow(model, row);
    return QString("%1\t%L2 EUR\t%3\n")
                .arg(balance->valuta().toString("dd.MM.yyyy"))
                .arg(balance->value(), 4, 'f', 2)
                .arg(balance->purpose());
}

void MemberHandler::selectedMemberId(QVariant id)
{
    delete m_member;
    delete m_bankAccount;
    delete m_sepaAccount;
    delete m_contribution;

    m_member = dao::MemberTableModel::findByMemberId(id);
    m_bankAccount = dao::BankAccountTableModel::findByMemberId(id);
    m_sepaAccount = dao::SepaAccountTableModel::findByMemberId(id);
    m_contribution = dao::ContributionTableModel::findLastEntryByMemberId(id);

    QSqlTableModel *contributionModel = dao::ContributionTableModel::createModel(id);
    m_contributionProxyTableModel->setModel(contributionModel);

    QSqlTableModel *balanceModel = dao::BalanceTableModel::createModel(id);
    m_balanceProxyTableModel->setModel(balanceModel);

    qDebug() << QString("Selected member id: %1").arg(m_member->memberId());

    emit memberChanged();
}

void MemberHandler::newMember()
{
    delete m_member;
    delete m_bankAccount;
    delete m_sepaAccount;
    delete m_contribution;

    m_member = new entity::Member();
    m_bankAccount = new entity::BankAccount();
    m_sepaAccount = new entity::SepaAccount();
    m_contribution = new entity::Contribution();

    m_contributionProxyTableModel->setModel(new QSqlTableModel());
    m_balanceProxyTableModel->setModel(new QSqlTableModel());

    emit memberChanged();
}

void MemberHandler::newContribution()
{
    delete m_contribution;
    m_contribution = new entity::Contribution();
    emit memberChanged();
}

} // namespace gui
} // namespace membermanager
