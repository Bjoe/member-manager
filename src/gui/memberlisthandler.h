#ifndef MEMBERMANAGER_GUI_MEMBERLISTHANDLER_H
#define MEMBERMANAGER_GUI_MEMBERLISTHANDLER_H

#include <QObject>
#include <QVariant>

#include "gui/proxytablemodel.h"
#include "entity/member.h"

namespace membermanager {
namespace gui {

class MemberListHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isInactive READ isInactive WRITE setAndSelectInactiveMember NOTIFY memberStateChanged)
    Q_PROPERTY(membermanager::entity::Member::State memberState READ memberState WRITE selectMemberState NOTIFY memberStateChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *memberProxyModel READ memberProxyModel NOTIFY memberProxyModelChanged)

public:
    explicit MemberListHandler(QObject *parent = 0);

    ProxyTableModel *memberProxyModel() const;

    entity::Member::State memberState() const;
    void selectMemberState(entity::Member::State state);

    bool isInactive() const;
    void setAndSelectInactiveMember(bool deleted);

signals:
    void memberStateChanged();
    void memberProxyModelChanged();
    void selectMemberId(QVariant id);

public slots:
    void onRefresh(const QVariant& column, const Qt::SortOrder order);
    void onSelectedRow(int row);

private:
    entity::Member::State m_memberState;
    ProxyTableModel *m_memberProxyTableModel;

    void createMemberProxyTableModel(const QVariant& column = "memberId", const Qt::SortOrder order = Qt::SortOrder::DescendingOrder);
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERLISTHANDLER_H
