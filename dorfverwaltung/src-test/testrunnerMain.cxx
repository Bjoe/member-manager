
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <iostream>
#include "litesql.hpp"
#include "../src/dorfmanagement.hpp"

using namespace litesql;
using namespace MemberManagement;

int main(int argc, char *argv)
{
	try {
	    // Wird das benoetigt ?
        //DorfManagement db("sqlite3", "database=dorf.db");
        //db.verbose = true;
        //db.create(); // bei existierenden Schema, Exception!

        CppUnit::TextUi::TestRunner runner;
        CppUnit::TestFactoryRegistry &registerFactory = CppUnit::TestFactoryRegistry::getRegistry();
        runner.addTest( registerFactory.makeTest() );
        runner.run();

	} catch(SQLError e) {
        std::cout << e; // Wird das benoetigt ?
	}
	std::string foo;
	std::cin >> foo;

	return 0;
}
