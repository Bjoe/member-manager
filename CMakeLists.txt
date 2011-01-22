project(Dorfverwaltung)

# The version number.
set (MemberManager_VERSION_MAJOR 0)
set (MemberManager_VERSION_MINOR 1)

cmake_minimum_required(VERSION 2.8)

find_package(Qt4 4.5.2 COMPONENTS QtCore QtGui QtSql REQUIRED)

# The following are required to uses Dart and the Cdash dashboard
enable_testing(true)
#include(CTest)
include(Utils.cmake)

# i would to see more projects using these defaults
ADD_DEFINITIONS( "-Wall -ansi" )
# ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

set(CMAKE_INCLUDE_CURRENT_DIR ON) 

add_subdirectory(gui-Qt)
