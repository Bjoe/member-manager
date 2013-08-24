#ifndef MEMBERMANAGER_GUI_MEMBERUICONTROLLER_H
#define MEMBERMANAGER_GUI_MEMBERUICONTROLLER_H

#include <QObject>
#include <QSqlTableModel>

namespace membermanager {
namespace gui {

class MemberUiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSqlTableModel* memberTableModel READ memberTableModel NOTIFY memberTableModelChanged)

public:
    MemberUiController(QObject *parent = 0);

    QSqlTableModel* memberTableModel();

signals:
    void memberTableModelChanged();

public slots:
    void onDatabaseReady();

private:
    QSqlTableModel *m_tableModel;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_MEMBERUICONTROLLER_H
