#ifndef MEMBERMANAGER_GUI_SETTINGSDIALOG_H
#define MEMBERMANAGER_GUI_SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace membermanager
{
namespace gui
{

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    
private slots:
    void saveSettings();

private:
    QSettings settings;
    Ui::SettingsDialog *ui;
};


} // namespace gui
} // namespace membermanager
#endif // MEMBERMANAGER_GUI_SETTINGSDIALOG_H
