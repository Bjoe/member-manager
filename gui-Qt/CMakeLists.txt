
find_package(Qt4 4.5.2 COMPONENTS QtCore QtGui QtSql REQUIRED)
include(${QT_USE_FILE})

add_subdirectory(src)
add_subdirectory(test)

