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

    Q_PROPERTY(QList<QObject *> memberList READ memberList WRITE setMemberList NOTIFY memberListChanged)
    Q_PROPERTY(QString accountingInfo WRITE setAccountingInfo)
    Q_PROPERTY(QString purposeInfo WRITE setPurposeInfo)

public:
    explicit AccountingHandler(QObject *parent = 0);

    void setMemberList(const QList<QObject *>& memberList);
    QList<QObject *> memberList() const;

    void setAccountingInfo(const QString& accountingInfo);
    void setPurposeInfo(const QString& purposeInfo);

    Q_INVOKABLE void book(const QString& filename);

signals:
    void memberListChanged();

public slots:

private:
    QList<QObject *> m_memberList {};
    QString m_accountingInfo {};
    QString m_purposeInfo {};
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_ACCOUNTINGHANDLER_H
