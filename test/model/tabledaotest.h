#ifndef TABLEDAOTEST_H
#define TABLEDAOTEST_H

#include <QtTest/QtTest>
#include "testcoverageobject.h"

namespace membermanagertest
{
namespace model
{


class TableDaoTest : public qttestutil::TestCoverageObject
{
    Q_OBJECT
public:
    void initTest();

private slots:
    void testInsertNewRow();
};

}
}

#endif // TABLEDAOTEST_H
