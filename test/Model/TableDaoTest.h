#ifndef TABLEDAOTEST_H
#define TABLEDAOTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Model
{


class TableDaoTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testInsertNewRow();
};

}
}

#endif // TABLEDAOTEST_H
