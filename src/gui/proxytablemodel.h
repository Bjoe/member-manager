#ifndef MEMBERMANAGER_GUI_PROXYTABLEMODEL_H
#define MEMBERMANAGER_GUI_PROXYTABLEMODEL_H

#include <QVariant>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QSqlTableModel>

namespace membermanager {
namespace gui {

class ProxyTableModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ProxyTableModel(QObject *parent = 0);

    void reload(QSqlTableModel *sqlTableModel);
    bool select();

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    
signals:
    
public slots:

private:
    QModelIndex parent(const QModelIndex &child = QModelIndex()) const;

    QSqlTableModel *m_sqlTableModel;
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_PROXYTABLEMODEL_H
