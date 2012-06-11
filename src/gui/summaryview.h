#ifndef SUMMARYVIEW_H
#define SUMMARYVIEW_H

#include <QWidget>

namespace Ui {
class SummaryView;
}

namespace membermanager
{
namespace gui
{

class SummaryView : public QWidget
{
    Q_OBJECT
    
public:
    explicit SummaryView(QWidget *aParent = 0);
    ~SummaryView();

private slots:
    void calculate();

private:
    Ui::SummaryView *ui;
};

}
}
#endif // SUMMARYVIEW_H
