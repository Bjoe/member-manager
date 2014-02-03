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

    Q_PROPERTY(bool isInactive READ isInactive WRITE setBoolMemberState NOTIFY memberStateChanged)
    Q_PROPERTY(membermanager::entity::Member::State memberState READ memberState WRITE setMemberState NOTIFY memberStateChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *memberProxyModel READ memberProxyModel NOTIFY memberProxyModelChanged)

public:
    explicit MemberListHandler(QObject *parent = 0);

    void setMemberProxyModel(ProxyTableModel* model);
    ProxyTableModel *memberProxyModel() const;

    entity::Member::State memberState() const;
    void setMemberState(entity::Member::State state);

    bool isInactive() const;
    void setBoolMemberState(bool isInactive);

signals:
    void memberStateChanged();
    void memberProxyModelChanged();
    void selectMemberId(QVariant id);

public slots:
    void reset();
    void refresh(const QVariant& column = "memberId", const Qt::SortOrder order = Qt::SortOrder::AscendingOrder);
    void selectedRow(int row);

private:
    entity::Member::State m_memberState = entity::Member::State::active;
    ProxyTableModel *m_memberProxyTableModel = new ProxyTableModel(this);
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERLISTHANDLER_H
