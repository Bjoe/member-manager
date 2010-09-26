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

namespace ClubFrontendTest
{

TriggerThread::TriggerThread(QObject *aParent, Executor* const anExecutor) :
	QThread(aParent), mutex(), waitForThread(), executor(anExecutor)
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
	waitForThread.wakeAll();
	mutex.unlock();
	executor->doWork();
}

}
