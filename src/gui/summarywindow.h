#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtGui/QWidget>

#include "ui_summarywindow.h"

#include "summaryhandler.h"
#include "summarywriter.h"

namespace membermanager
{
namespace gui
{

class SummaryWindow : public QDialog, public SummaryWriter
{
    Q_OBJECT

public:
    SummaryWindow(QWidget *parent = 0);

    void addSummary(SummaryHandler *aHandler);

    virtual void writeContent(const QString &aContent);

private:
    Ui::SummaryWindow ui;
    QList<const SummaryHandler *> handlerList;

    void addButton(const SummaryHandler *aHandler);
};

}
}

#endif // SUMMARYWINDOW_H
