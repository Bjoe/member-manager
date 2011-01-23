/*
 * TriggerThread.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: joerg
 */

#include "TestUtils/TriggerThread.h"

namespace ClubFrontendTest
{

TriggerThread::TriggerThread ( QObject *aParent, Handler* const anExecutor,
                               const QModelIndex& anIndex ) :
        QThread ( aParent ), mutex(), waitForThread(), executor ( anExecutor ),
        modelIndex ( anIndex )
{
}

TriggerThread::~TriggerThread()
{
}

void TriggerThread::syncStart()
{
    mutex.lock();
    start();
    waitForThread.wait ( &mutex );
    mutex.unlock();
    QCoreApplication::processEvents();
    wait();
}

void TriggerThread::run()
{
    mutex.lock();

    emit
    triggered();

    emit
    triggeredModelIndex ( modelIndex );

    waitForThread.wakeAll();
    mutex.unlock();
    sleep ( 1 );
    if ( executor != 0 )
    {
        executor->handle();
    }
}

}
