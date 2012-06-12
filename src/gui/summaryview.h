#ifndef SUMMARYVIEW_H
#define SUMMARYVIEW_H

#include <QWidget>

namespace membermanager
{
namespace gui
{

namespace Ui
{
class SummaryView;
}


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
