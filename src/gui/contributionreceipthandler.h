#ifndef MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H
#define MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H

#include <QObject>
#include <QVariant>
#include <QList>

namespace membermanager {
namespace gui {

class ContributionReceiptHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> balanceList READ balanceList WRITE setBalanceList NOTIFY balanceListChanged)

public:
    explicit ContributionReceiptHandler(QObject *parent = 0);
    ~ContributionReceiptHandler();

    QList<QObject *> balanceList() const;
    void setBalanceList(const QList<QObject *> &balanceList);

    Q_INVOKABLE void createReceipt(QVariant memberId, int year);

signals:
    void balanceListChanged();

private:
    QList<QObject *> m_balanceList;

    void clearList();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H
