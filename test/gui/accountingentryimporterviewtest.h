#ifndef MEMBERMANAGERTEST_GUI_ACCOUNTINGENTRYIMPORTERVIEWTEST_H
#define MEMBERMANAGERTEST_GUI_ACCOUNTINGENTRYIMPORTERVIEWTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class AccountingEntryImporterViewTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testImport();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_ACCOUNTINGENTRYIMPORTERVIEWTEST_H
