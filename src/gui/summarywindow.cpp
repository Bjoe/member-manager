#include "gui/summarywindow.h"

namespace membermanager
{
namespace gui
{

SummaryWindow::SummaryWindow(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
}

void SummaryWindow::showSummary(const QString &aText)
{
    ui.textEdit->setText(aText);
}

void SummaryWindow::addButton(QPushButton *aButton)
{
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(aButton->sizePolicy().hasHeightForWidth());
    aButton->setSizePolicy(sizePolicy);

    ui.verticalLayout->addWidget(aButton);
}

}
}
