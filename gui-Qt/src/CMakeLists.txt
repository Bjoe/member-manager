
set(QT_FRONTEND_MOC_HEADERS
    MainWindow.h
    MemberDialog.h
    )

set(QT_FRONTEND_UI
    mainWindow.ui
    memberDialog.ui
    )

set(QT_FRONTEND_SRC
    MainWindow.cpp
    MemberDialog.cpp
    MemberModel.cpp
    MemberFilter.cpp
    )

# Setze Sourcen fuer die tests
set(QT_FRONTEND_MOC_HEADERS ${QT_FRONTEND_MOC_HEADERS} PARENT_SCOPE)
set(QT_FRONTEND_UI ${QT_FRONTEND_UI} PARENT_SCOPE)
set(QT_FRONTEND_SRC ${QT_FRONTEND_SRC} PARENT_SCOPE)


qt4_wrap_cpp(MOC_OUTFILES ${QT_FRONTEND_MOC_HEADERS})

# Die ui_xxxx.h files werden im CMAKE_CURRENT_BINARY_DIR erzeugt.
qt4_wrap_ui(UI_OUTFILES ${QT_FRONTEND_UI})
include_directories(${CMAKE_CURRENT_BINARY_DIR})


add_executable(Dorfverwaltung-GUI-Qt main.cpp ${QT_FRONTEND_SRC} ${MOC_OUTFILES} ${UI_OUTFILES})
target_link_libraries(Dorfverwaltung-GUI-Qt ${QT_LIBRARIES})

