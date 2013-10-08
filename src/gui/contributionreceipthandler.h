#ifndef MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H
#define MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QList>

namespace membermanager {
namespace gui {

class ContributionReceiptHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double sum READ sum WRITE setSum NOTIFY sumChanged)
    Q_PROPERTY(QList<QObject *> balanceList READ balanceList WRITE setBalanceList NOTIFY balanceListChanged)

public:
    explicit ContributionReceiptHandler(QObject *parent = 0);
    ~ContributionReceiptHandler();

    QList<QObject *> balanceList() const;
    void setBalanceList(const QList<QObject *> &balanceList);

    double sum() const;
    void setSum(double sum);

    Q_INVOKABLE void createReceipt(QVariant memberId, int year);
    Q_INVOKABLE void removeRow(int row);
    Q_INVOKABLE void saveReceipt(int id, const QString &urlPath, const QString& urlFilename, int year);

signals:
    void balanceListChanged();
    void sumChanged();

private:
    double m_sum {};
    QList<QObject *> m_balanceList {};

    void clearList();
    double calculateSum();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H
