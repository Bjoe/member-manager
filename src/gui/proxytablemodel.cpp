#include "proxytablemodel.h"

#include <QDebug>

namespace membermanager {
namespace gui {

ProxyTableModel::ProxyTableModel(QObject *parent) :
    QAbstractListModel(parent),
    m_roles(),
    m_sqlTableModel(new QSqlTableModel())
{
}

QSqlTableModel *ProxyTableModel::getModel() const
{
    return m_sqlTableModel;
}

void ProxyTableModel::reload(QSqlTableModel *sqlTableModel)
{
    delete m_sqlTableModel;
    m_sqlTableModel = sqlTableModel;
    m_sqlTableModel->select();

    m_roles.clear();
    int colCount = m_sqlTableModel->columnCount();
    for(int i = 0; i < colCount; ++i) {
        QVariant role = m_sqlTableModel->headerData(i, Qt::Horizontal);
        m_roles[Qt::UserRole + 1 + i] = role.toByteArray();
    }
    emit modelReloaded();
}

QHash<int, QByteArray> ProxyTableModel::roleNames() const
{
    qDebug() << QString("Get roles %1").arg(m_roles.size());
    return m_roles;
}

bool ProxyTableModel::select()
{
    return m_sqlTableModel->select();
}

int ProxyTableModel::rowCount(const QModelIndex &parent) const
{
    int count = m_sqlTableModel->rowCount(parent);
    qDebug() << QString("Get rowCount %1").arg(count);
    return count;
}

QVariant ProxyTableModel::data(const QModelIndex &index, int role) const
{
    qDebug() << QString("Get data role: %1").arg(role);
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
