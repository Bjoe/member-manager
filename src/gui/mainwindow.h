#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "ui_mainwindow.h"

namespace membermanager
{
namespace gui
{

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    Ui::MainWindow ui;
    QListWidget *listWidget;
    QStackedWidget *stackedLayout;
};

}
}

#endif // MAINWINDOW_H
