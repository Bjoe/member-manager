#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtGui/QWidget>

#include "ui_summarywindow.h"

#include "summaryhandler.h"

namespace ClubFrontend
{
namespace Gui
{

class SummaryWindow : public QWidget, public SummaryHandler
{
    Q_OBJECT

public:
    SummaryWindow ( QWidget *parent = 0 );

    void showSummary ( const QString &aText );
    void addButton ( QPushButton *aButton );

private:
    Ui::SummaryWindow ui;
};

}
}

#endif // SUMMARYWINDOW_H
