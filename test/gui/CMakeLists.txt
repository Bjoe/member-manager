
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(../)

qt4_add_test(contributiondialog contributiondialogtest.cpp)
qt4_add_test(contributionreceiptdialog contributionreceiptdialogtest.cpp)
qt4_add_test(connectiondialog connectiondialogtest.cpp)
qt4_add_test(balancedialog balancedialogtest.cpp)
qt4_add_test(mainwindow mainwindowtest.cpp)
qt4_add_test(memberdetailview memberdetailviewtest.cpp)
qt4_add_test(memberdebtview memberdebtviewtest.cpp)
qt4_add_test(summaryview summaryviewtest.cpp)
qt4_add_test(paymentview paymentviewtest.cpp)
qt4_add_test(settingsdialog settingsdialogtest.cpp)
