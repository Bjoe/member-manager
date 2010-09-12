/*
 * MemberFilterTest.cpp
 *
 *  Created on: Jul 6, 2010
 *      Author: joerg
 */

#include "MemberFilterTest.h"

#include "MemberFilter.h"

#include <QString>

namespace ClubFrontendTest {

void MemberFilterTest::testSetDeleted() {
	ClubFrontend::MemberFilter filter;
	filter.setDeleted();

	QCOMPARE(filter.getFilter(),QString("deleted=1"));
}

}
