
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

add_library(databaseUtilsLib STATIC DatabaseUtils.cpp ReadSqlFile.cpp)
set(triggerThreadUtil TriggerThread.h)
qt4_wrap_cpp(moc_triggerThreadUtil ${triggerThreadUtil})
add_library(utilTestLib STATIC SummaryHandlerMock.cpp ${moc_triggerThreadUtil} TriggerThread.cpp DialogButtonBoxHandler.cpp)

set(test_additional_lib
 memberManagerLib 
 databaseUtilsLib
 utilTestLib
)

set(test_additional
)

qt4_add_test(memberDetailModel MemberDetailModelTest.cpp)
qt4_add_test(memberDialog MemberDetailModelTest.cpp)
qt4_add_test(memberFilter MemberFilterTest.cpp)
qt4_add_test(memberModel MemberModelTest.cpp)
qt4_add_test(member MemberTest.cpp)
qt4_add_test(cashSumSummary CashSumSummaryTest.cpp)
qt4_add_test(contributionDialog ContributionDialogTest.cpp)
qt4_add_test(contributionModel ContributionModelTest.cpp)
qt4_add_test(connectionDialog ConnectionDialogTest.cpp)
qt4_add_test(countMemberSummary CountMemberSummaryTest.cpp)
qt4_add_test(debitSumSummary DebitSumSummaryTest.cpp)
qt4_add_test(kassaModel KassaModelTest.cpp)
qt4_add_test(saldoDialog SaldoDialogTest.cpp)
qt4_add_test(saldoSumModel SaldoSumModelTest.cpp)
qt4_add_test(saldoModel SaldoModelTest.cpp)
qt4_add_test(summaryWindow SummaryWindowTest.cpp)
qt4_add_test(mainWindow MainWindowTest.cpp)
