/*
 * MemberFilterTest.cpp
 *
 *  Created on: Jul 6, 2010
 *      Author: joerg
 */

#include "MemberFilterTest.h"

#include "Model/MemberFilter.h"

#include <QString>

namespace ClubFrontendTest
{
namespace Model
{
  
void MemberFilterTest::testSetDeleted()
{
    ClubFrontend::Model::MemberFilter filter;
    filter.setDeleted ( true );

    QCOMPARE ( filter.getFilter(), QString ( "deleted='true'" ) );
}

void MemberFilterTest::testSetDeletedFalse()
{
    ClubFrontend::Model::MemberFilter filter;
    filter.setDeleted ( false );

    QCOMPARE ( filter.getFilter(), QString ( "deleted='false'" ) );
}

}
}

QTEST_MAIN ( ClubFrontendTest::Model::MemberFilterTest )
#include "MemberFilterTest.moc"
