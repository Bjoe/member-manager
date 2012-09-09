#ifndef MEMBERMANAGERTEST_GUI_MEMBERLISTDELEGATETEST_H
#define MEMBERMANAGERTEST_GUI_MEMBERLISTDELEGATETEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace gui
{

class MemberListDelegateTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

private slots:
    void testCreateEditor();
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_MEMBERLISTDELEGATETEST_H
