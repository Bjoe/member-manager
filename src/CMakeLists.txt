
set(QT_MOC_HEADERS
    gui/mainwindow.h
    gui/memberdetailview.h
    gui/connectiondialog.h
    gui/balancedialog.h
    gui/contributiondialog.h
    gui/summarywindow.h

    summaryhandler.h
    )

set(QT_UI
    gui/mainwindow.ui
    gui/connectiondialog.ui
    gui/balancedialog.ui
    gui/contributiondialog.ui
    gui/summarywindow.ui
    )

set(QT_SRCS
    gui/mainwindow.cpp
    gui/memberdetailview.cpp
    gui/connectiondialog.cpp
    gui/balancedialog.cpp
    gui/contributiondialog.cpp
    gui/summarywindow.cpp

    dao/kassamodel.cpp
    dao/databasestructure.cpp
    dao/memberdao.cpp
    dao/balancedao.cpp
    dao/contributiondao.cpp

    accounting/balanceentry.cpp
    accounting/contributionentry.cpp

    member.cpp
    cashsumsummary.cpp
    debitsumsummary.cpp
    contributionreceipt.cpp
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
