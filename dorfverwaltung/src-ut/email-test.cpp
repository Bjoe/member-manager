#include <UnitTest++.h>
#include <exception>

#include "../src/e-mail.hpp"

TEST(EMailOk) {
	EMail email("joerg@localhost.de");
	CHECK_EQUAL("joerg@localhost.de",email.getAddress());
}

TEST(EmailFail) {
    CHECK_THROW(EMail email("joerglocalhostde"), std::exception);
}
