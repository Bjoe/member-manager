#ifndef MEMBERMANAGER_ACCOUNTING_BALANCEPERSISTER_H
#define MEMBERMANAGER_ACCOUNTING_BALANCEPERSISTER_H

#include <QObject>
#include <QVariant>
#include <QTableWidget>

namespace membermanager
{
namespace accounting
{

class BalancePersister : public QObject
{
    Q_OBJECT

public:
    BalancePersister(QTableWidget *anAccountingEntryTable, QObject *aParent = 0);
    virtual ~BalancePersister() {}

public slots:
    void booking() const;

private:
    QVariant getData(int aRow, int aColumn) const;

    QTableWidget *accountingEntryTable;
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_BALANCEPERSISTER_H
