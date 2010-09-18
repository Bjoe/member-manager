#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "ui_mainWindow.h"
#include "MemberModel.h"

namespace ClubFrontend
{

class MainWindow: public QMainWindow
{
Q_OBJECT

public:
	MainWindow(MemberModel & aDataSource, QWidget * parent = 0);

private:
	Ui::MainWindow ui;
	MemberModel & dataSource;
};

}

#endif // MAINWINDOW_H
