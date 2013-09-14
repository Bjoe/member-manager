#ifndef MEMBERMANAGER_GUI_SUMMARYHANDLER_H
#define MEMBERMANAGER_GUI_SUMMARYHANDLER_H

#include <QObject>

namespace membermanager {
namespace gui {

class SummaryHandler : public QObject
{
    Q_OBJECT
public:
    explicit SummaryHandler(QObject *parent = 0);

signals:

public slots:

};

} // namespace gui
} // namespace membermanager

#endif // MEMBERMANAGER_GUI_SUMMARYHANDLER_H
