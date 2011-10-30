
# The following are required to uses Dart and the Cdash dashboard
enable_testing(true)
#include(CTest)

if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

find_package(QtTestUtil)

find_package(Qt4 4.7.3 COMPONENTS QtTest REQUIRED)
include(${QT_USE_FILE})

# Test Konfigurationen
set(DATABASEDRIVER QSQLITE)
set(DATABASE dorfverw.dat)
set(SQLTESTFILE "${PROJECT_SOURCE_DIR}/testdaten.sql")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../src ${CMAKE_CURRENT_BINARY_DIR}/../src ${QT_TEST_UTIL_INCLUDE_DIR})

set(test_additional_lib
 memberManagerLib
 ${QT_TEST_UTIL_LIBRARIES}
)

set(test_additional
)

add_subdirectory(gui)
add_subdirectory(model)

qt4_add_test(member membertest.cpp)
qt4_add_test(memberfactory memberfactorytest.cpp)
qt4_add_test(cashsumsummary cashsumsummarytest.cpp testutil/summaryhandlermock.cpp)
qt4_add_test(countmembersummary countmembersummarytest.cpp testutil/summaryhandlermock.cpp)
qt4_add_test(debitsumsummary debitsumsummarytest.cpp testutil/summaryhandlermock.cpp)
