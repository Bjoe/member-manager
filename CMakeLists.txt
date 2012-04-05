project(MemberManager)

cmake_minimum_required(VERSION 2.8)

include(QtBuildUtil)

# The version number.
set (MemberManager_VERSION_MAJOR 0)
set (MemberManager_VERSION_MINOR 1)
set (MemberManager_VERSION_PATCH 0)

find_package(Qt4 4.7.0 REQUIRED QtCore QtGui QtSql)

set(CMAKE_INCLUDE_CURRENT_DIR ON) 

find_doxygen()

add_subdirectory(src)

# The following are required to uses CTest, Dart and the Cdash dashboard
enable_testing(true)
include(CTest)
add_subdirectory(test)
