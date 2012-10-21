
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../)

qt4_add_test(memberdao memberdaotest.cpp)
qt4_add_test(balancedao balancedaotest.cpp)
qt4_add_test(contributiondao contributiondaotest.cpp)

qt4_test(cashaccountdao cashaccountdaotest.cpp)
