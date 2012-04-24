
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../)

qt4_add_test(memberfilter memberfiltertest.cpp)
qt4_add_test(membermodel membermodeltest.cpp)
qt4_add_test(kassamodel kassamodeltest.cpp)
qt4_add_test(saldomodel saldomodeltest.cpp)
qt4_add_test(memberdao memberdaotest.cpp)
qt4_add_test(balancedao balancedaotest.cpp)
qt4_add_test(contributiondao contributiondaotest.cpp)
