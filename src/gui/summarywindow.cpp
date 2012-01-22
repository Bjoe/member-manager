#include "gui/summarywindow.h"

namespace membermanager
{
namespace gui
{

SummaryWindow::SummaryWindow(QWidget *parent) : QDialog(parent), handlerList()
{
    ui.setupUi(this);

    connect(ui.buttonBox, SIGNAL(rejected()), SLOT(close()));
}

void SummaryWindow::addSummary(SummaryHandler *aHandler)
{
    addButton(aHandler);
    aHandler->setWriter(this);
    handlerList.append(aHandler);
}

void SummaryWindow::writeContent(const QString &aContent)
{
    ui.textEdit->insertHtml(aContent);
}

void SummaryWindow::addButton(const SummaryHandler *aHandler)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);

    QPushButton *button = new QPushButton(aHandler->getTitle());
    button->setObjectName(aHandler->getTitle());

    sizePolicy.setHeightForWidth(button->sizePolicy().hasHeightForWidth());
    button->setSizePolicy(sizePolicy);

    ui.verticalLayout->addWidget(button);

    connect(button, SIGNAL(clicked()), aHandler, SLOT(handleHtmlText()));
}

}
}
