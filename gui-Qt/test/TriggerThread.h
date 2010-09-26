/*
 * TriggerThread.h
 *
 *  Created on: Sep 23, 2010
 *      Author: joerg
 */

#ifndef TRIGGERTHREAD_H_
#define TRIGGERTHREAD_H_

#include <QThread>
#include <QAction>
#include <QMutex>
#include <QWaitCondition>
#include "Executor.h"

namespace ClubFrontendTest
{

class TriggerThread: public QThread
{
Q_OBJECT

public:
	TriggerThread(QObject *aParent, Executor* const anExecutor);
	virtual ~TriggerThread();

	void syncStart();

protected:
	void run();

signals:
	void triggered();

private:
	mutable QMutex mutex;
	mutable QWaitCondition waitForThread;
	Executor* const executor;
};

}

#endif /* TRIGGERTHREAD_H_ */
