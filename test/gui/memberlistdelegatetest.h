#ifndef MEMBERMANAGERTEST_GUI_MEMBERLISTDELEGATETEST_H
#define MEMBERMANAGERTEST_GUI_MEMBERLISTDELEGATETEST_H

#include <QtTest/QtTest>
#include <QString>
#include <QAbstractItemModel>
#include "testcoverageobject.h"
#include "database/databaseutil.h"

namespace membermanagertest
{
namespace gui
{

class MemberListDelegateTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT

public:
    MemberListDelegateTest();

private slots:
    void initTestCase();
    void initTest();

    void testCreateEditor();
    void testSetEditorData();
    void testSetModelData();

private:
    qttestutil::database::DatabaseUtil database;

    QString data(int aRow, int aColumn, QAbstractItemModel *aModel);
};

} // namespace gui
} // namespace membermanagertest

#endif // MEMBERMANAGERTEST_GUI_MEMBERLISTDELEGATETEST_H
