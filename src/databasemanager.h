#ifndef MEMBERMANAGER_MANAGERENGINE_H
#define MEMBERMANAGER_MANAGERENGINE_H

#include <QObject>
#include <QString>

namespace membermanager {

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    DatabaseManager(QObject *parent = 0);
signals:
    void databaseReady();

public slots:
    void onLoadSqlFile(QString filename);
};

} // namespace membermanager

#endif // MEMBERMANAGER_MANAGERENGINE_H
