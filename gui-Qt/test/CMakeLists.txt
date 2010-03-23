
find_package(Qt4 4.5.2 COMPONENTS QtTest REQUIRED)
include(${QT_USE_FILE})

set(QT_FRONTEND_TEST
    TestData.cpp
    mainwindowtest.cpp
    memberdialogtest.cpp
    )

set(QT_FRONTEND_TEST_MOC_HEADERS
    mainwindowtest.h
    memberdialogtest.h
    )

# Setze src Verzeichniss
foreach(_current ${QT_FRONTEND_SRC})
    set(QT_FRONTEND_SRC_DIR ${QT_FRONTEND_SRC_DIR} ../src/${_current})
endforeach(_current ${QT_FRONTEND_SRC})

foreach(_current ${QT_FRONTEND_MOC_HEADERS})
    set(QT_FRONTEND_MOC_HEADERS_DIR ${QT_FRONTEND_MOC_HEADERS_DIR} ../src/${_current})
endforeach(_current ${QT_FRONTEND_MOC_HEADERS})

qt4_wrap_cpp(MOC_OUTFILES_TEST ${QT_FRONTEND_TEST_MOC_HEADERS} ${QT_FRONTEND_MOC_HEADERS_DIR})


foreach(_current ${QT_FRONTEND_UI})
    set(QT_FRONTEND_UI_DIR ${QT_FRONTEND_UI_DIR} ../src/${_current})
endforeach(_current ${QT_FRONTEND_UI})

# Die ui_xxxx.h files werden im CMAKE_CURRENT_BINARY_DIR erzeugt.
qt4_wrap_ui(UI_OUTFILES_TEST ${QT_FRONTEND_UI_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ../src)


include_directories(${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})

add_executable(Dorfverwaltung-GUI-Qt-Test main.cpp ${QT_FRONTEND_TEST} ${QT_FRONTEND_SRC_DIR} ${MOC_OUTFILES_TEST} ${UI_OUTFILES_TEST})
target_link_libraries(Dorfverwaltung-GUI-Qt-Test ${QT_LIBRARIES} ${GTEST_LIBRARY} ${GMOCK_LIBRARY})

add_test(Dorfverwaltung-GUI-Qt-Test Dorfverwaltung-GUI-Qt-Test)
