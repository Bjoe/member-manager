#ifndef MEMBERMANAGER_GUI_MEMBERHANDLER_H
#define MEMBERMANAGER_GUI_MEMBERHANDLER_H

#include <QObject>
#include <QAbstractItemModel>

#include "gui/proxytablemodel.h"

namespace membermanager {
namespace gui {

class MemberHandler : public QObject
{
    Q_OBJECT

public:
    MemberHandler(QObject *parent = 0);

    ProxyTableModel *getProxyModel();

public slots:
    void onDatabaseReady();

private:
    ProxyTableModel *m_proxyTableModel;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERHANDLER_H
