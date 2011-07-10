project(MemberManager)

cmake_minimum_required(VERSION 2.8)

include(QtBuildUtil)

# The version number.
set (MemberManager_VERSION_MAJOR 0)
set (MemberManager_VERSION_MINOR 1)
set (MemberManager_VERSION_PATCH 0)

find_package(Qt4 4.7.3 COMPONENTS QtCore QtGui QtSql REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON) 

find_doxygen()

add_subdirectory(src)
add_subdirectory(test)
