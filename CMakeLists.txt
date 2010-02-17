project(Dorfverwaltung)
cmake_minimum_required(VERSION 2.8)

# The following are required to uses Dart and the Cdash dashboard
#enable_testing()
#include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(GTest) # Wird fuer GMock benoetigt
find_package(GMock REQUIRED)

add_subdirectory(gui-Qt)

