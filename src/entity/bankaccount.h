#ifndef MEMBERMANAGER_ENTITY_BANKACCOUNT_H
#define MEMBERMANAGER_ENTITY_BANKACCOUNT_H

#include <QObject>
#include <QString>
#include "QDjangoModel.h"

namespace membermanager {
namespace entity {

class BankAccount : public QDjangoModel
{
    Q_OBJECT

    Q_CLASSINFO("__meta__", "db_table=BankAccount")
    Q_CLASSINFO("bankAccountId", "primary_key=true db_index=true unique=true auto_increment=true")

    Q_PROPERTY(int bankAccountId READ bankAccountId WRITE setBankAccountId)
    Q_PROPERTY(int memberId READ memberId WRITE setMemberId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString accountNumber READ accountNumber WRITE setAccountNumber)
    Q_PROPERTY(QString code READ code WRITE setCode)

public:

    int bankAccountId() const;
    void setBankAccountId(int id);

    int memberId() const;
    void setMemberId(int id);

    QString name() const;
    void setName(QString name);

    QString accountNumber() const;
    void setAccountNumber(QString number);

    QString code() const;
    void setCode(QString code);

private:
    QString m_name;
    QString m_accountNumber;
    QString m_code;
    int m_memberId;
    int m_bankaccountId;
};

} // namespace entity
} // namespace membermanager

#endif // MEMBERMANAGER_ENTITY_BANKACCOUNT_H
