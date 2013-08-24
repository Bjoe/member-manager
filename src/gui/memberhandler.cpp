#include "memberhandler.h"

#include <QDebug>
#include <QSqlTableModel>

#include "dao/membertablemodel.h"

namespace membermanager {
namespace gui {

MemberHandler::MemberHandler(QObject *parent)
    : QObject(parent),
      m_proxyTableModel(new ProxyTableModel())
{
}

ProxyTableModel *MemberHandler::getProxyModel()
{
    return m_proxyTableModel;
}

void MemberHandler::onDatabaseReady()
{
    QSqlTableModel *model = dao::MemberTableModel::createModel();
    m_proxyTableModel->reload(model);
    m_proxyTableModel->select();

    qDebug() << QString("Database ready. Selected row count: %1").arg(m_proxyTableModel->rowCount());
}



} // namespace gui
} // namespace membermanager
