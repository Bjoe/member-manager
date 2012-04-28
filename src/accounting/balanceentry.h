#ifndef BALANCEENTRY_H
#define BALANCEENTRY_H

#include <QSqlRecord>
#include <QDate>

#include "model/balancedao.h"

namespace membermanager {
namespace model{class BalanceDao;}

namespace accounting
{

class BalanceEntry
{

public:
    BalanceEntry(int aMemberId = 0);

    int getMemberId() const;
    void setValue(double aValue);
    double getValue() const;
    void setValuta(const QDate &aDate);
    QDate getValuta() const;
    void setPurpose(const QString &aPurpose);
    QString getPurpose() const;
    void setInfo(const QString &anInfo);
    QString getInfo() const;
    void setAccount(int anAccount);
    int getAccount() const;

    friend class model::BalanceDao;

private:
    QSqlRecord balanceRecord;

    void setValueOnField(int aIndex, QVariant::Type aType, const QVariant &aValue);
};

}
}

#endif // BALANCEENTRY_H
