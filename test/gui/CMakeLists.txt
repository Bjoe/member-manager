
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../)

qt4_add_test(contributiondialog contributiondialogtest.cpp)
qt4_add_test(connectiondialog connectiondialogtest.cpp)
qt4_add_test(saldodialog saldodialogtest.cpp)
qt4_add_test(summarywindow summarywindowtest.cpp)
qt4_add_test(mainwindow mainwindowtest.cpp)
qt4_add_test(membermapper membermappertest.cpp)
