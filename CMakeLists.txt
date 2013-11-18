cmake_minimum_required(VERSION 2.8.11)

project(MemberManager)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" CACHE PATH "cmake modul path")
include(BuildUtil)

# The version number.
set (MemberManager_VERSION_MAJOR 0)
set (MemberManager_VERSION_MINOR 1)
set (MemberManager_VERSION_PATCH 0)

add_definitions(-std=c++11)

# QML debuggen
add_definitions(-DQT_QML_DEBUG)
# and set environment
# QML_COMPILER_DUMP=1
# QML_DISABLE_OPTIMIZER=1
# argument:
# $ membermanager -qmljsdebugger=port:3768,block


# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# cmake example from http://qt-project.org/doc/qt-5.1/qtdoc/cmake-manual.html
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(QDJ REQUIRED qdjango-db)

include_directories(
  "${QDJ_INCLUDE_DIRS}"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_BINARY_DIR}/src"
)

if(${DOC})
    find_doxygen()
endif(${DOC})

add_subdirectory(src)

if(${TEST})
    # The following are required to uses Dart and the Cdash dashboard
    enable_testing(true)
    include(CTest)
    add_subdirectory(test)
endif(${TEST})
