cmake_minimum_required(VERSION 2.8.9)

project(MemberManager)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" CACHE PATH "cmake modul path")
include(BuildUtil)

# The version number.
set (MemberManager_VERSION_MAJOR 0)
set (MemberManager_VERSION_MINOR 1)
set (MemberManager_VERSION_PATCH 0)

find_package(Qt4 4.7.0 REQUIRED QtCore QtGui QtSql)
find_package(PkgConfig REQUIRED)
pkg_check_modules(AQB REQUIRED aqbanking)
pkg_check_modules(GWN REQUIRED gwenhywfar)
find_package(QIABanking)

include_directories(
  "${QIABANKING_INCLUDE_DIRS}"
  "${AQB_INCLUDE_DIRS}" 
  "${GWN_INCLUDE_DIRS}"
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
