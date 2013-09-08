#ifndef MEMBERMANAGER_GUI_MEMBERHANDLER_H
#define MEMBERMANAGER_GUI_MEMBERHANDLER_H

#include <QObject>
#include <QAbstractItemModel>

#include "gui/proxytablemodel.h"
#include "entity/member.h"
#include "entity/bankaccount.h"
#include "entity/contribution.h"

namespace membermanager {
namespace gui {

class MemberHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isInactive READ isInactive WRITE setAndSelectInactiveMember NOTIFY memberStateChanged)
    Q_PROPERTY(membermanager::entity::Member::State memberState READ memberState WRITE selectMemberState NOTIFY memberStateChanged)
    Q_PROPERTY(membermanager::entity::Member *member READ member NOTIFY memberChanged)
    Q_PROPERTY(membermanager::entity::BankAccount *bankAccount READ bankAccount NOTIFY memberChanged)
    Q_PROPERTY(membermanager::entity::Contribution *contribution READ contribution NOTIFY memberChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *memberProxyModel READ memberProxyModel NOTIFY memberProxyModelChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *contributionProxyModel READ contributionProxyModel NOTIFY contribuitonProxyModelChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *balanceProxyModel READ balanceProxyModel NOTIFY balanceProxyModelChanged)

public:
    MemberHandler(QObject *parent = 0);

    ProxyTableModel *memberProxyModel() const;
    ProxyTableModel *contributionProxyModel() const;
    ProxyTableModel *balanceProxyModel() const;
    entity::Member *member() const;
    entity::BankAccount *bankAccount() const;
    entity::Contribution *contribution() const;

    entity::Member::State memberState() const;
    void selectMemberState(entity::Member::State state);

    bool isInactive() const;
    void setAndSelectInactiveMember(bool deleted);

signals:
    void memberChanged();
    void memberProxyModelChanged();
    void contribuitonProxyModelChanged();
    void balanceProxyModelChanged();
    void memberStateChanged();
    void bankAccountChanged();
    void contributionChanged();

public slots:
    void onDatabaseReady();
    void onMemberSelected(int row);

private:
    entity::Member::State m_memberState;
    entity::Member *m_member;
    entity::BankAccount *m_bankaccount;
    entity::Contribution *m_contribution;

    ProxyTableModel *m_memberProxyTableModel;
    ProxyTableModel *m_contributionProxyTableModel;
    ProxyTableModel *m_balanceProxyTableModel;

    void createMemberProxyTableModel();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERHANDLER_H
