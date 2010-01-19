#include <boost/test/unit_test.hpp>

#include "../src/EMailException.hpp"

using namespace Dorfverwaltung;

BOOST_AUTO_TEST_SUITE(EmailExceptionTest)

BOOST_AUTO_TEST_CASE(EmailExceptionGetMessage)
{
    EMailException emailException("TestException");
    BOOST_CHECK_EQUAL("TestException",emailException.getMessage());
}

BOOST_AUTO_TEST_CASE(EMailExceptionWhat)
{
    EMailException emailException("TestWhat");
    BOOST_CHECK_EQUAL("TestWhat",emailException.what());
}

BOOST_AUTO_TEST_SUITE_END()
