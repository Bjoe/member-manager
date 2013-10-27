#include "proxytablemodel.h"

namespace membermanager {
namespace gui {

ProxyTableModel::ProxyTableModel(QObject *parent) :
    QAbstractListModel(parent),
    m_roles(),
    m_sqlTableModel(new QSqlTableModel())
{}

ProxyTableModel::ProxyTableModel(QSqlTableModel *model, QObject *parent) :
    QAbstractListModel(parent),
    m_roles(),
    m_sqlTableModel(model)
{
    int colCount = m_sqlTableModel->columnCount();
    for(int i = 0; i < colCount; ++i) {
        QVariant role = m_sqlTableModel->headerData(i, Qt::Horizontal);
        m_roles[Qt::UserRole + 1 + i] = role.toByteArray();
    }
}

QSqlTableModel *ProxyTableModel::getModel() const
{
    return m_sqlTableModel;
}

QHash<int, QByteArray> ProxyTableModel::roleNames() const
{
    return m_roles;
}

bool ProxyTableModel::select()
{
    return m_sqlTableModel->select();
}

int ProxyTableModel::rowCount(const QModelIndex &parent) const
{
    int count = m_sqlTableModel->rowCount(parent);
    return count;
}

QVariant ProxyTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value = m_sqlTableModel->data(index, role);
    if(role >= Qt::UserRole) {
        int columnIndex = role - Qt::UserRole - 1;
        QModelIndex modelIndex = m_sqlTableModel->index(index.row(), columnIndex);
        value = m_sqlTableModel->data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

} // namespace gui
} // namespace membermanager
