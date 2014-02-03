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

    Q_INVOKABLE void selectYear(int year);

signals:
    void cashProxyModelChanged();
    void cashAccountChanged();
    void cashAccountModelChanged();
    void statusMessage(QString message);
    void progress(double value);

public slots:
    void refresh();
    void selectedRow(int row);
    void importFile(const QString& urlFilename);

private:
    int m_year = 0;
    ProxyTableModel *m_cashProxyModel = new ProxyTableModel(this);
    entity::CashAccount *m_cashAccount = new entity::CashAccount();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_CASHIMPORTHANDLER_H
