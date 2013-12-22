
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC OFF)

# cmake example from http://qt-project.org/doc/qt-5.1/qtdoc/cmake-manual.html
find_package(Qt5Test)

# Test Konfigurationen
set(DATABASEDRIVER QSQLITE)
set(DATABASE dorfverw.dat)
set(SQLTESTFILE "${PROJECT_SOURCE_DIR}/testdaten.sql")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/testconfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/testconfig.h"
  )

include_directories(
  "${CMAKE_CURRENT_BINARY_DIR}"
  "${CMAKE_CURRENT_BINARY_DIR}/../src"
  "${CMAKE_CURRENT_BINARY_DIR}/accounting"
  "${CMAKE_CURRENT_BINARY_DIR}/dao"
  "${CMAKE_CURRENT_BINARY_DIR}/gui"
  "${CMAKE_CURRENT_BINARY_DIR}/sumoperator"
)

set(test_additional_lib
 memberManagerLib
 ${QAQBANKING_LIBRARIES}
 ${AQB_LDFLAGS}
 ${GWN_LDFLAGS}
 ${QDJ_LDFLAGS}
 Qt5::Widgets
 Qt5::Qml
 Qt5::Quick
)

set(test_additional
)

add_subdirectory(gui)
add_subdirectory(dao)
add_subdirectory(accounting)

qt_test(databaseManager databasemanagertest.cpp)
