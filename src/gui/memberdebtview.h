#ifndef MEMBERMANAGER_GUI_MEMBERDEBTVIEW_H
#define MEMBERMANAGER_GUI_MEMBERDEBTVIEW_H

#include <QWidget>

namespace membermanager
{
namespace gui
{

namespace Ui
{
class MemberDebtView;
}

class MemberDebtView : public QWidget
{
    Q_OBJECT
    
public:
    explicit MemberDebtView(QWidget *parent = 0);
    ~MemberDebtView();
    
public slots:
    void calculate();

private:
    Ui::MemberDebtView *ui;
};


} // namespace gui
} // namespace membermanager
#endif // MEMBERMANAGER_GUI_MEMBERDEBTVIEW_H
