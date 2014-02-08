#ifndef MEMBERMANAGER_GUI_FEEDEBTHANDLER_H
#define MEMBERMANAGER_GUI_FEEDEBTHANDLER_H

#include <QObject>
#include <QDate>
#include <QList>

#include "entity/member.h"

namespace membermanager {
namespace gui {

class FeeDebtHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> debtModel READ debtModel WRITE setDebtModel NOTIFY debtModelChanged)
    Q_PROPERTY(QDate valuta READ valuta WRITE setValuta NOTIFY valutaChanged)
    Q_PROPERTY(membermanager::entity::Member::State memberState READ memberState WRITE setMemberState NOTIFY memberStateChanged)
    Q_PROPERTY(bool isInactive READ isInactive WRITE setBoolMemberState NOTIFY memberStateChanged)

public:
    explicit FeeDebtHandler(QObject *parent = 0);

    QList<QObject *> debtModel() const;
    void setDebtModel(QList<QObject *> model);

    entity::Member::State memberState() const;
    void setMemberState(entity::Member::State state);
    bool isInactive() const;
    void setBoolMemberState(bool isInactive);
    void setValuta(const QDate& valuta);
    QDate valuta() const;

    Q_INVOKABLE void copyToClipboard(int row);
    Q_INVOKABLE void copyAllToClipboard();

signals:
    void debtModelChanged();
    void memberStateChanged();
    void valutaChanged();
    void statusMessage(QString message);
    void progress(double value);

public slots:
    void calculate();
    void reset();

private:
    entity::Member::State m_memberState = entity::Member::State::active;
    QDate m_valuta = QDate::currentDate();
    QList<QObject *> m_debtModel {};
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_FEEDEBTHANDLER_H
