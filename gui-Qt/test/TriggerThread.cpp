/*
 * TriggerThread.cpp
 *
 *  Created on: Sep 23, 2010
 *      Author: joerg
 */

#include "TriggerThread.h"
#include <QMutexLocker>
#include <QWidget>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QCoreApplication>
#include <QEventLoop>

namespace ClubFrontendTest
{

TriggerThread::TriggerThread(QObject *aParent, Handler* const anExecutor,
		const QModelIndex& anIndex) :
	QThread(aParent), mutex(), waitForThread(), executor(anExecutor),
			modelIndex(anIndex)
{
}

TriggerThread::~TriggerThread()
{
}

void TriggerThread::syncStart()
{
	mutex.lock();
	start();
	waitForThread.wait(&mutex);
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
	triggeredModelIndex(modelIndex);

	waitForThread.wakeAll();
	mutex.unlock();
	sleep(1);
	executor->handle();
}

}
