/*
 * TriggerThread.h
 *
 *  Created on: Sep 23, 2010
 *      Author: joerg
 */

#ifndef TRIGGERTHREAD_H_
#define TRIGGERTHREAD_H_

#include <QtCore>

#include "TestUtils/Handler.h"

namespace ClubFrontendTest
{

class TriggerThread: public QThread
{
    Q_OBJECT

public:
    TriggerThread ( QObject *aParent, Handler* const anExecutor = 0, const QModelIndex& anIndex = QModelIndex() );
    virtual ~TriggerThread();

    void syncStart();

protected:
    void run();

signals:
    void triggered();
    void triggeredModelIndex ( const QModelIndex& anIndex );

private:
    mutable QMutex mutex;
    mutable QWaitCondition waitForThread;
    Handler* const executor;
    const QModelIndex& modelIndex;
};

}

#endif /* TRIGGERTHREAD_H_ */
