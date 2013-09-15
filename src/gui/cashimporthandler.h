#ifndef MEMBERMANAGER_GUI_CASHIMPORTHANDLER_H
#define MEMBERMANAGER_GUI_CASHIMPORTHANDLER_H

#include <QObject>

#include "gui/proxytablemodel.h"
#include "entity/cashaccount.h"

namespace membermanager {
namespace gui {

class CashImportHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(membermanager::gui::ProxyTableModel *cashProxyModel READ cashProxyModel NOTIFY cashProxyModelChanged)
    Q_PROPERTY(membermanager::entity::CashAccount *cashAccount READ cashAccount NOTIFY cashAccountChanged)

public:
    explicit CashImportHandler(QObject *parent = 0);

    ProxyTableModel *cashProxyModel() const;
    entity::CashAccount *cashAccount() const;

signals:
    void cashProxyModelChanged();
    void cashAccountChanged();

public slots:
    void onDatabaseReady();
    void onCashSelected(int row);

private:
    ProxyTableModel *m_cashProxyModel;
    entity::CashAccount *m_cashAccount;

    void createCashProxyTableModel();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_CASHIMPORTHANDLER_H
