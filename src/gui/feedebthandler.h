#ifndef MEMBERMANAGER_GUI_FEEDEBTHANDLER_H
#define MEMBERMANAGER_GUI_FEEDEBTHANDLER_H

#include <QObject>
#include <QList>

#include "entity/member.h"

namespace membermanager {
namespace gui {

class FeeDebtHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> debtModel READ debtModel WRITE setDebtModel NOTIFY debtModelChanged)
    Q_PROPERTY(membermanager::entity::Member::State memberState READ memberState WRITE setMemberState NOTIFY memberStateChanged)

public:
    explicit FeeDebtHandler(QObject *parent = 0);

    QList<QObject *> debtModel() const;
    void setDebtModel(QList<QObject *> model);

    entity::Member::State memberState() const;
    void setMemberState(entity::Member::State state);

    Q_INVOKABLE void copyToClipboard(int row);
    Q_INVOKABLE void copyAllToClipboard();

signals:
    void debtModelChanged();
    void memberStateChanged();
    void statusMessage(QString message);
    void progress(double value);

public slots:
    void onCalculate();
    void onRefresh();

private:
    entity::Member::State m_memberState;
    QList<QObject *> m_debtModel;

    void clearList();
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_FEEDEBTHANDLER_H
