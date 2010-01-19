/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * dorfverwaltung
 * Copyright (C) Joerg-Christian Boehme 2009 <joerg@chaosdorf.de>
 *
 * dorfverwatung is free software copyrighted by Joerg-Christian Boehme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name ``Joerg-Christian Boehme'' nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * dorfverwaltung IS PROVIDED BY Joerg-Christian Boehme ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Joerg-Christian Boehme OR ANY OTHER CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "club-member-test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ClubMemberTest);

MemberManagement::DorfManagement createDb() {
	MemberManagement::DorfManagement memberdb("sqlite3", "database=test.db");
	memberdb.verbose = true;
	//memberdb.create(); bei existierenden Schema, Exception!
	return memberdb;
}

void ClubMemberTest::testName()
{
	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember villager(memberdb);
	villager.setName("Hansolo");
	CPPUNIT_ASSERT_EQUAL(string("Hansolo"),villager.getName());
}

void ClubMemberTest::testVorname()
{
    MemberManagement::DorfManagement memberdb = createDb();
	ClubMember villager(memberdb);
	villager.setFirstname("Luke");
	CPPUNIT_ASSERT_EQUAL(string("Luke"),villager.getFirstname());
}

void ClubMemberTest::testMemberId()
{
   	MemberManagement::DorfManagement memberdb = createDb();
	ClubMember villager(memberdb);
	villager.setId(123);
	CPPUNIT_ASSERT_EQUAL(123,villager.getId());
}

void ClubMemberTest::testEntryDate()
{
	using namespace boost::gregorian;

	date entryDate(2006,Jul,14);

	MemberManagement::DorfManagement memberdb = createDb();

	ClubMember villager(memberdb);
	villager.setEntryDate(entryDate);

	date testEntryDate(2006,Jul,14);
	CPPUNIT_ASSERT(testEntryDate == villager.getEntryDate());
}
