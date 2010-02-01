#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "ui_mainWindow.h"

namespace GuiManagement
{

class MainWindow : public QMainWindow, public Ui::MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

};

}

#endif // MAINWINDOW_H
