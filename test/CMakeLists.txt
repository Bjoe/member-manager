
# The following are required to uses Dart and the Cdash dashboard
enable_testing(true)
#include(CTest)

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
  "${PROJECT_SOURCE_DIR}/TestConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/TestConfig.h"
  )

include_directories(../src ${CMAKE_CURRENT_BINARY_DIR}/../src ${QT_TEST_UTIL_INCLUDE_DIR})

set(test_additional_lib
 memberManagerLib
 ${QT_TEST_UTIL_LIBRARIES}
)

set(test_additional
)

add_subdirectory(Gui)
add_subdirectory(Model)

qt4_add_test(member MemberTest.cpp)
qt4_add_test(cashSumSummary CashSumSummaryTest.cpp TestUtils/SummaryHandlerMock.cpp)
qt4_add_test(countMemberSummary CountMemberSummaryTest.cpp TestUtils/SummaryHandlerMock.cpp)
qt4_add_test(debitSumSummary DebitSumSummaryTest.cpp TestUtils/SummaryHandlerMock.cpp)
