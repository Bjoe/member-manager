#ifndef MEMBERMANAGER_GUI_ACCOUNTINGHANDLER_H
#define MEMBERMANAGER_GUI_ACCOUNTINGHANDLER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDate>

namespace membermanager {
namespace gui {

class AccountingHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate valuta READ valuta WRITE setValuta NOTIFY valutaChanged)
    Q_PROPERTY(QString purpose READ purpose WRITE setPurpose NOTIFY purposeChanged)
    Q_PROPERTY(QString accountingInfo READ accountingInfo WRITE setAccountingInfo NOTIFY accountingInfoChanged)
    Q_PROPERTY(QList<QObject *> accountingDataList READ accountingDataList WRITE setAccountingDataList NOTIFY accountingDataListChanged)

public:
    explicit AccountingHandler(QObject *parent = 0);
    ~AccountingHandler();

    void setValuta(const QDate& date);
    QDate valuta() const;

    void setPurpose(const QString& text);
    QString purpose() const;

    void setAccountingInfo(const QString& text);
    QString accountingInfo() const;

    void setAccountingDataList(const QList<QObject *>& list);
    QList<QObject *> accountingDataList() const;

    Q_INVOKABLE void book(const QString& filename);

signals:
    void accountingDataListChanged();
    void valutaChanged();
    void purposeChanged();
    void accountingInfoChanged();

public slots:
    void onRefresh();

private:
    QDate m_valuta;
    QString m_purpose {};
    QString m_accountingInfo {};
    QList<QObject *> m_memberAccountingDataList {};

    void clearList();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_ACCOUNTINGHANDLER_H
