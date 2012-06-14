#ifndef MEMBERMANAGER_GUI_PAYMENTVIEW_H
#define MEMBERMANAGER_GUI_PAYMENTVIEW_H

#include <QWidget>
#include <QTableWidgetItem>

namespace membermanager {
namespace gui {

namespace Ui {
class PaymentView;
}

class PaymentView : public QWidget
{
    Q_OBJECT
    
public:
    explicit PaymentView(QWidget *parent = 0);
    ~PaymentView();
    
public slots:
    void calculate();
    void memberCollection();

private:
    Ui::PaymentView *ui;

    QTableWidgetItem *createTextItem(const QString aText);
};


} // namespace gui
} // namespace membermanager
#endif // MEMBERMANAGER_GUI_PAYMENTVIEW_H
