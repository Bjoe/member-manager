#ifndef MEMBERMANAGER_GUI_PROXYTABLEMODEL_H
#define MEMBERMANAGER_GUI_PROXYTABLEMODEL_H

#include <QByteArray>
#include <QHash>
#include <QVariant>
#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QSqlTableModel>


/*
 * Some NOTE:
 * Use only QAbstractListModel ... other model (for example QAbstractTableModel etc.) make no sense in QML.
 * To use C++ Models do not use
 * QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const
 * method from QSqlTableModel !
 */
namespace membermanager {
namespace gui {

class ProxyTableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ProxyTableModel(QObject *parent = 0);

    // TODO add Move constructors

    void setModel(QSqlTableModel* model);
    QSqlTableModel *getModel() const;

    bool select();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int,QByteArray> roleNames() const;

private:
    QHash<int, QByteArray> m_roles {};
    QSqlTableModel *m_sqlTableModel = new QSqlTableModel();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_PROXYTABLEMODEL_H
