#ifndef MEMBERMANAGER_MANAGERENGINE_H
#define MEMBERMANAGER_MANAGERENGINE_H

#include <QtCore/QObject>
#include <QtCore/QString>

namespace membermanager {

class ManagerEngine : public QObject
{
    Q_OBJECT

public:
    ManagerEngine(QObject *parent = 0);

public slots:
    void onLoadSqlFile(QString filename);
};

} // namespace membermanager

#endif // MEMBERMANAGER_MANAGERENGINE_H
