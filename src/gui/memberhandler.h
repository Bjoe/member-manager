#ifndef MEMBERMANAGER_GUI_MEMBERHANDLER_H
#define MEMBERMANAGER_GUI_MEMBERHANDLER_H

#include <QObject>
#include <QSqlTableModel>

#include "gui/proxytablemodel.h"
#include "entity/member.h"
#include "entity/bankaccount.h"
#include "entity/sepaaccount.h"
#include "entity/contribution.h"

namespace membermanager {
namespace gui {

class MemberHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(membermanager::entity::Member *member READ member NOTIFY memberChanged)
    Q_PROPERTY(membermanager::entity::BankAccount *bankAccount READ bankAccount NOTIFY memberChanged)
    Q_PROPERTY(membermanager::entity::SepaAccount *sepaAccount READ sepaAccount NOTIFY memberChanged)
    Q_PROPERTY(membermanager::entity::Contribution *contribution READ contribution NOTIFY memberChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *contributionProxyModel READ contributionProxyModel NOTIFY memberChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *balanceProxyModel READ balanceProxyModel NOTIFY memberChanged)

public:
    MemberHandler(QObject *parent = 0);

    ProxyTableModel *contributionProxyModel() const;
    ProxyTableModel *balanceProxyModel() const;
    entity::Member *member() const;
    entity::BankAccount *bankAccount() const;
    entity::SepaAccount *sepaAccount() const;
    entity::Contribution *contribution() const;

    Q_INVOKABLE void copyBalanceToClipboard(int row);
    Q_INVOKABLE void copyAllBalanceToClipboard();

signals:
    void memberChanged();

public slots:
    void reset();
    void selectedMemberId(QVariant id);
    void newMember();
    void newContribution();

private:
    entity::Member *m_member = new entity::Member();
    entity::BankAccount *m_bankAccount = new entity::BankAccount();
    entity::SepaAccount *m_sepaAccount = new entity::SepaAccount();
    entity::Contribution *m_contribution = new entity::Contribution();

    ProxyTableModel *m_contributionProxyTableModel = new ProxyTableModel(this);
    ProxyTableModel *m_balanceProxyTableModel = new ProxyTableModel(this);

    QString createText(const QSqlTableModel* model, int row);
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERHANDLER_H
