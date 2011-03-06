#ifndef CONTRIBUTIONMODELTEST_H
#define CONTRIBUTIONMODELTEST_H

#include <QtTest/QtTest>

namespace ClubFrontendTest
{
namespace Model
{
  
class ContributionModelTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testModel();
    void testGetColumns();
    void testChangeInfo();
    void testNewFeeDonation();
    void testNewMemberId();
};

}
}

#endif // CONTRIBUTIONMODELTEST_H
