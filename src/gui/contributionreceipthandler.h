#ifndef MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H
#define MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QVariant>

namespace membermanager {
namespace gui {

class ContributionReceiptHandler : public QObject
{
    Q_OBJECT
public:
    explicit ContributionReceiptHandler(QObject *parent = 0);

    Q_INVOKABLE QString showReceipt(QVariant memberId, int year);
};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_CONTRIBUTIONRECEIPTHANDLER_H
