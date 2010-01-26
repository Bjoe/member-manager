#include <boost/test/unit_test.hpp>

#include "../src/EMailException.hpp"
#include "../src/EMail.hpp"

using namespace ClubBackend;

BOOST_AUTO_TEST_SUITE(EmailTest)

BOOST_AUTO_TEST_CASE(EMailOk)
{
    EMail email("joerg@localhost.de");
    BOOST_CHECK_EQUAL("joerg@localhost.de",email.getAddress());
}

BOOST_AUTO_TEST_CASE(EmailFail)
{
    BOOST_CHECK_THROW(EMail email("joerglocalhostde"), EMailException::EMailException);
}

BOOST_AUTO_TEST_SUITE_END()
