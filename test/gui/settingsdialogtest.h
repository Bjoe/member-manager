#ifndef MEMBERMANAGERTEST_GUI_SETTINGSDIALOGTEST_H
#define MEMBERMANAGERTEST_GUI_SETTINGSDIALOGTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class SettingsDialogTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testSettings();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_SETTINGSDIALOGTEST_H
