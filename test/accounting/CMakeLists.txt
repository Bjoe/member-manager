
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../)

qt4_add_test(balanceentry balanceentrytest.cpp)
qt4_add_test(contributionentry contributionentrytest.cpp)
qt4_add_test(pay paytest.cpp)

qt4_test(transactionimporter transactionimportertest.cpp)
qt4_test(balancepersister balancepersistertest.cpp)
