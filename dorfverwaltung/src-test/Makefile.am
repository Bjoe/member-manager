
bin_PROGRAMS = \
	btest

btest_SOURCES = \
	testrunnerMain.cxx\
	foo-bar-test.cpp \
	foo-bar-test.hpp \
	../src/club-member.cpp \
	../src/club-member.hpp \
	club-member-test.cpp \
	club-member-test.hpp \
	../src/dorfmanagement.cpp \
	../src/dorfmanagement.hpp

btest_LDADD = \
	-lecpg_compat \
	-lecpg \
	-lpq \
	-lpgtypes \
	$(LiteSql_LIBS) \
	$(UnitTest_LIBS)

AM_CPPFLAGS = \
	$(LiteSql_CFLAGS)\
	$(UnitTest_CFLAGS)

## File created by the gnome-build tools

