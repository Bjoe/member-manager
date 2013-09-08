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
    Q_PROPERTY(membermanager::gui::ProxyTableModel *proxyModel READ proxyModel NOTIFY proxyModelChanged)

public:
    MemberHandler(QObject *parent = 0);

    ProxyTableModel *proxyModel() const;
    entity::Member *member() const;
    entity::BankAccount *bankAccount() const;
    entity::Contribution *contribution() const;

    entity::Member::State memberState() const;
    void selectMemberState(entity::Member::State state);

    bool isInactive() const;
    void setAndSelectInactiveMember(bool deleted);

signals:
    void memberChanged();
    void proxyModelChanged();
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

    ProxyTableModel *m_proxyTableModel;

    void createProxyTableModel();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERHANDLER_H
