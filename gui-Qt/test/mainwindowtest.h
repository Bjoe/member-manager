#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "mainwindow.h"

namespace ClubFrontendTest
{

class MainWindowTest : public QObject
{
	Q_OBJECT

private slots:
	void instanz();
	void loadMembers();
};

}

#endif
