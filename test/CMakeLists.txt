
find_package(Qt4 4.5.2 COMPONENTS QtTest REQUIRED)
include(${QT_USE_FILE})

# Test Konfigurationen
set(DATABASEDRIVER QSQLITE)
set(DATABASE dorfverw.dat)
set(SQLTESTFILE "${CMAKE_CURRENT_SOURCE_DIR}/testdaten.sql")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/TestConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/TestConfig.h"
  )

include_directories(../src ${CMAKE_CURRENT_BINARY_DIR}/../src)

add_library(databaseUtilsLib STATIC TestUtils/DatabaseUtils.cpp TestUtils/ReadSqlFile.cpp)
set(triggerThreadUtil TestUtils/TriggerThread.h)
qt4_wrap_cpp(moc_triggerThreadUtil ${triggerThreadUtil})
add_library(utilTestLib STATIC TestUtils/SummaryHandlerMock.cpp ${moc_triggerThreadUtil} TestUtils/TriggerThread.cpp TestUtils/DialogButtonBoxHandler.cpp)

set(test_additional_lib
 memberManagerLib 
 databaseUtilsLib
 utilTestLib
)

set(test_additional
)

add_subdirectory(Gui)
add_subdirectory(Model)

qt4_add_test(cashSumSummary CashSumSummaryTest.cpp)
qt4_add_test(countMemberSummary CountMemberSummaryTest.cpp)
qt4_add_test(debitSumSummary DebitSumSummaryTest.cpp)
