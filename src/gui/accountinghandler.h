#ifndef MEMBERMANAGER_GUI_ACCOUNTINGHANDLER_H
#define MEMBERMANAGER_GUI_ACCOUNTINGHANDLER_H

#include <QObject>
#include <QString>
#include <QList>

namespace membermanager {
namespace gui {

class AccountingHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> accountingDataList READ accountingDataList WRITE setAccountingDataList NOTIFY accountingDataListChanged)

public:
    explicit AccountingHandler(QObject *parent = 0);

    void setAccountingDataList(const QList<QObject *>& list);
    QList<QObject *> accountingDataList() const;

    Q_INVOKABLE void book(const QString& filename);

signals:
    void accountingDataListChanged();

public slots:

private:
    QList<QObject *> m_memberAccountingDataList {};
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_ACCOUNTINGHANDLER_H
