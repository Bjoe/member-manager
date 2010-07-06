#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "ui_mainWindow.h"
#include "DataSource.h"

namespace ClubFrontend
{

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(DataSource & aDataSource, QWidget * parent = 0);

private:
	DataSource & dataSource;
};

}

#endif // MAINWINDOW_H
