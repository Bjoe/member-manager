#ifndef TESTFIXTURE_HPP_INCLUDED
#define TESTFIXTURE_HPP_INCLUDED

#include <iostream>
#include "../src/dorfmanagement.hpp"

struct MemberDB {
	MemberDB();
	~MemberDB();
	MemberManagement::DorfManagement database;
};

#endif // TESTFIXTURE_HPP_INCLUDED
