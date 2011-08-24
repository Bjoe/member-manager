
set(QT_MOC_HEADERS
    gui/mainwindow.h
    gui/membermapper.h
    gui/connectiondialog.h
    gui/saldodialog.h
    gui/saldosumdialog.h
    gui/contributiondialog.h
    gui/summarywindow.h

    countmembersummary.h
    cashsumsummary.h
    debitsumsummary.h
    )

set(QT_UI
    gui/mainwindow.ui
    gui/connectiondialog.ui
    gui/saldodialog.ui
    gui/saldosumdialog.ui
    gui/contributiondialog.ui
    gui/summarywindow.ui
    )

set(QT_SRCS
    gui/mainwindow.cpp
    gui/membermapper.cpp
    gui/connectiondialog.cpp
    gui/saldodialog.cpp
    gui/saldosumdialog.cpp
    gui/contributiondialog.cpp
    gui/summarywindow.cpp

    model/membermodel.cpp
    model/kassamodel.cpp
    model/saldomodel.cpp
    model/saldosummodel.cpp
    model/contributionmodel.cpp
    model/memberfilter.cpp
    model/databasestructure.cpp
    model/memberdao.cpp
    model/tabledao.cpp

    member.cpp
    summaryhandler.cpp
    countmembersummary.cpp
    cashsumsummary.cpp
    debitsumsummary.cpp
    )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

qt4_wrap_cpp(MOC_OUTFILES ${QT_MOC_HEADERS})

# Die ui_xxxx.h files werden im CMAKE_CURRENT_BINARY_DIR erzeugt.
qt4_wrap_ui(UI_OUTFILES ${QT_UI})

include(${QT_USE_FILE})

add_library(memberManagerLib STATIC ${QT_SRCS} ${MOC_OUTFILES} ${UI_OUTFILES})

add_executable(memberManager main.cpp)

target_link_libraries(memberManager memberManagerLib ${QT_LIBRARIES})
