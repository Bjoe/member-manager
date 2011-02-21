
find_package(Qt4 4.5.2 COMPONENTS QtTest REQUIRED)
include(${QT_USE_FILE})

find_library(TESTUTILS_LIB qttestutils)
find_library(TESTUTILS_DATABASELIB qtdatabasetestutils)
find_path(TESTUTILS_INC NAMES TriggerThread.h DatabaseUtils.h DialogButtonBoxHandler.h Handler.h)

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

include_directories(../src ${CMAKE_CURRENT_BINARY_DIR}/../src ${TESTUTILS_INC})

set(test_additional_lib
 memberManagerLib
 ${TESTUTILS_LIB}
 ${TESTUTILS_DATABASELIB}
)

set(test_additional
)

add_subdirectory(Gui)
add_subdirectory(Model)

qt4_add_test(cashSumSummary CashSumSummaryTest.cpp TestUtils/SummaryHandlerMock.cpp)
qt4_add_test(countMemberSummary CountMemberSummaryTest.cpp TestUtils/SummaryHandlerMock.cpp)
qt4_add_test(debitSumSummary DebitSumSummaryTest.cpp TestUtils/SummaryHandlerMock.cpp)
