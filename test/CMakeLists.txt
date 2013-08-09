
if(CMAKE_CROSSCOMPILING)
    include(Coverage)
endif(CMAKE_CROSSCOMPILING)

find_package(QtTestUtil)

if(${QT5})
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC OFF)

    # cmake example from http://qt-project.org/doc/qt-5.1/qtdoc/cmake-manual.html
    find_package(Qt5Test)

else(${QT5})
    find_package(Qt4 4.8 REQUIRED QtTest)
    include(${QT_USE_FILE})

endif(${QT5})

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
  "${QT_TEST_UTIL_INCLUDE_DIRS}"
)

set(test_additional_lib
 memberManagerLib
 ${QIABANKING_LIBRARIES}
 ${AQB_LIBRARIES}
 ${GWN_LIBRARIES}
 ${QT_TEST_UTIL_LIBRARIES}
 ${QT_GUI_TEST_UTIL_LIBRARIES}
 ${QT_DATABASE_TEST_UTIL_LIBRARIES}
)

set(test_additional
)

add_subdirectory(gui)
add_subdirectory(dao)
add_subdirectory(accounting)

qt_add_test(member membertest.cpp)
