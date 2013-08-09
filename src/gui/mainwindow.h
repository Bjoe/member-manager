#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>

#include "ui_mainwindow.h"
#include "gui/memberdetailview.h"
#include "gui/accountingentryimporterview.h"

namespace membermanager
{
namespace gui
{

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    void loadDatabase();

private slots:
    void showSettingsDialog();
    void showDatabaseDialog();
    void showOpenFileDialog();

private:
    ::Ui::MainWindow ui;
    QListWidget *listWidget;
    QStackedWidget *stackedLayout;
    MemberDetailView *memberDetailView;
    MemberDetailView *deletedMemberView;
    AccountingEntryImporterView *accountingEntryImporterView;

};

}
}

#endif // MAINWINDOW_H
