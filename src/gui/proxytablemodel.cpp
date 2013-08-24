#include "proxytablemodel.h"

namespace membermanager {
namespace gui {

ProxyTableModel::ProxyTableModel(QObject *parent) :
    QAbstractItemModel(parent),
    m_sqlTableModel(new QSqlTableModel())
{
}

void ProxyTableModel::reload(QSqlTableModel *sqlTableModel)
{
    delete m_sqlTableModel;
    m_sqlTableModel = sqlTableModel;
}

bool ProxyTableModel::select()
{
    return m_sqlTableModel->select();
}

QModelIndex ProxyTableModel::index(int row, int column, const QModelIndex &parent) const
{
    return m_sqlTableModel->index(row, column, parent);
}

QModelIndex ProxyTableModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int ProxyTableModel::rowCount(const QModelIndex &parent) const
{
    return m_sqlTableModel->rowCount(parent);
}

int ProxyTableModel::columnCount(const QModelIndex &parent) const
{
    return m_sqlTableModel->columnCount(parent);
}

QVariant ProxyTableModel::data(const QModelIndex &index, int role) const
{
    return m_sqlTableModel->data(index, role);
}

} // namespace gui
} // namespace membermanager
