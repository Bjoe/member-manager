project(Dorfverwaltung)

# The version number.
# TODO Versionsnummer mit Git Nummer verbinden.
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

# http://snikt.net/index.php/2010/04/01/howto-use-cmake-with-cc-projects
# check if doxygen is even installed
find_package(Doxygen REQUIRED)

# prepare doxygen configuration file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

# add doxygen as target
add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

# cleanup $build/api-doc on "make clean"
set_property(DIRECTORY APPEND PROPERTY
	     ADDITIONAL_MAKE_CLEAN_FILES api-doc)

# add doxygen as dependency to doc-target
get_target_property(DOC_TARGET doc TYPE)
if(NOT DOC_TARGET)
	add_custom_target(doc)
endif()
add_dependencies(doc doxygen)

# install HTML API documentation and manual pages
#set(DOC_PATH "share/doc/${CPACK_PACKAGE_NAME}-${VERSION}")
#
#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/html
#         DESTINATION ${DOC_PATH}
#       )
#
# install man pages into packages, scope is now project root..
#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/man/man3
#         DESTINATION share/man/man3/
#       )

add_subdirectory(src)
add_subdirectory(test)
