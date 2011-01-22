
configure_file (
  "${PROJECT_SOURCE_DIR}/TestConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/TestConfig.h"
  )

include_directories(../)

qt4_add_test(memberDialog MemberDialogTest.cpp)
qt4_add_test(contributionDialog ContributionDialogTest.cpp)
qt4_add_test(connectionDialog ConnectionDialogTest.cpp)
qt4_add_test(saldoDialog SaldoDialogTest.cpp)
qt4_add_test(summaryWindow SummaryWindowTest.cpp)
qt4_add_test(mainWindow MainWindowTest.cpp)
