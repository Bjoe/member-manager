#include "memberuicontroller.h"
#include <QDebug>

namespace membermanager {
namespace gui {

MemberUiController::MemberUiController(QObject *parent)
    : QObject(parent), m_tableModel(new QSqlTableModel())
{
}

QSqlTableModel* MemberUiController::memberTableModel()
{
    return m_tableModel;
}

void MemberUiController::onDatabaseReady()
{
    m_tableModel->setTable("member");
    m_tableModel->select();

    qDebug() << QString("Database ready. Selected row count: %1").arg(m_tableModel->rowCount());

    emit memberTableModelChanged();
}

} // namespace gui
} // namespace membermanager
