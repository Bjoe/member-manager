#ifndef MEMBERMANAGER_GUI_MEMBERHANDLER_H
#define MEMBERMANAGER_GUI_MEMBERHANDLER_H

#include <QObject>
#include <QAbstractItemModel>

#include "gui/proxytablemodel.h"
#include "entity/member.h"

namespace membermanager {
namespace gui {

class MemberHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(membermanager::entity::Member *member READ member NOTIFY memberChanged)
    Q_PROPERTY(membermanager::gui::ProxyTableModel *proxyModel READ proxyModel NOTIFY proxyModelChanged)

public:
    MemberHandler(QObject *parent = 0);

    ProxyTableModel *proxyModel();
    entity::Member *member();

signals:
    void memberChanged();
    void proxyModelChanged();

public slots:
    void onDatabaseReady();
    void onMemberSelected(int row);

private:
    entity::Member *m_member;
    ProxyTableModel *m_proxyTableModel;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERHANDLER_H
