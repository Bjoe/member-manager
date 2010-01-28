#include <boost/test/unit_test.hpp>
#include "TestFixture.hpp"

#include <vector>

#include "../src/dorfmanagement.hpp"
#include "../src/EMail.hpp"

#include "../src/Ressourcen.hpp"

using namespace ClubBackend;

BOOST_AUTO_TEST_SUITE(RessourcenTest)

BOOST_FIXTURE_TEST_CASE(ShellAccount, MemberDB)
{
	Ressourcen ressourcen(database);

	ressourcen.setShellAccount("Hackbarth");

	BOOST_CHECK_EQUAL("Hackbarth",ressourcen.getShellAccount());
}

BOOST_FIXTURE_TEST_CASE(EmailIntern, MemberDB)
{
	EMail email("foo@bar.cc");

	Ressourcen ressourcen(database);

	ressourcen.setEmailIntern(email);
	BOOST_CHECK_EQUAL("foo@bar.cc",ressourcen.getEmailIntern().getAddress());
}

BOOST_FIXTURE_TEST_CASE(EmailCCC, MemberDB)
{
	EMail email("bar@foo.cc");

	Ressourcen ressourcen(database);

	ressourcen.setEmailCcc(email);
	BOOST_CHECK_EQUAL("bar@foo.cc",ressourcen.getEmailCcc().getAddress());
}

BOOST_AUTO_TEST_CASE(GetFieldTypes)
{
	std::vector<litesql::FieldType> fields;
	Ressourcen::getFieldTypes(fields);

	BOOST_CHECK_EQUAL("Ressourcen_.id_",fields[0].fullName());
}

BOOST_FIXTURE_TEST_CASE(withRecord, MemberDB)
{
	litesql::Record record;

	Ressourcen(database, record);
}

BOOST_AUTO_TEST_SUITE_END()
