#ifndef MEMBERMANAGER_ACCOUNTING_STATEMENTENTRY_H
#define MEMBERMANAGER_ACCOUNTING_STATEMENTENTRY_H

#include <QString>
#include <QDateTime>
#include <QVariant>
#include <QSqlRecord>

#include "dao/cashaccountdao.h"

namespace membermanager
{
namespace dao {class CashAccountDao;}
namespace accounting
{

class StatementEntry
{
public:
    StatementEntry(int aKeyId);
    int getId() const;
    void setDeleted(bool deleted);
    bool isDeleted() const;
    void setPrimanota(QString aPrimanota);
    QString getPrimanota() const;
    void setValuta(QDateTime aValuta);
    QDateTime getValuta() const;
    void setDate(QDateTime aDate);
    QDateTime getDate() const;
    void setValue(double aValue);
    double getValue() const;
    void setTransactionCode(int aCode);
    int getTransactionCode() const;
    void setTransactionText(QString aText);
    QString getTransactionText() const;
    void setRemoteName(QString aName);
    QString getRemoteName() const;
    void setRemoteBankCode(QString aCode);
    QString getRemoteBankCode() const;
    void setRemoteAccountNumber(QString aNumber);
    QString getRemoteAccountNumber() const;
    void setPurpose(QString aText);
    QString getPurpose() const;
    void setMemberId(int anId);
    int getMemberId() const;
    void setBooked(bool booked);
    bool isBooked() const;

    friend class dao::CashAccountDao;

private:
    QSqlRecord statementRecord;

    void setValueOnField(int aIndex, const QVariant::Type aType, const QVariant &aValue);
};

} // namespace accounting
} // namespace membermanager

#endif // MEMBERMANAGER_ACCOUNTING_STATEMENTENTRY_H
