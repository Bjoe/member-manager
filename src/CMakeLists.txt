
if(NOT ${QT5})
    set(QT_MOC_HEADERS
        gui/mainwindow.h
        gui/memberdetailview.h
        gui/connectiondialog.h
        gui/balancedialog.h
        gui/contributiondialog.h
        gui/contributionreceiptdialog.h
        gui/summaryview.h
        gui/memberdebtview.h
        gui/paymentview.h
        gui/accountingentryimporterview.h
        gui/settingsdialog.h

        accounting/balancepersister.h
    )

    qt4_wrap_cpp(MOC_OUTFILES ${QT_MOC_HEADERS})

endif(NOT ${QT5})

set(QT_UI
    gui/mainwindow.ui
    gui/memberdetailview.ui
    gui/connectiondialog.ui
    gui/balancedialog.ui
    gui/contributiondialog.ui
    gui/contributionreceiptdialog.ui
    gui/summaryview.ui
    gui/memberdebtview.ui
    gui/paymentview.ui
    gui/accountingentryimporterview.ui
    gui/settingsdialog.ui
    )

set(QT_SRCS
    gui/mainwindow.cpp
    gui/memberdetailview.cpp
    gui/connectiondialog.cpp
    gui/balancedialog.cpp
    gui/contributiondialog.cpp
    gui/contributionreceiptdialog.cpp
    gui/summaryview.cpp
    gui/memberdebtview.cpp
    gui/paymentview.cpp
    gui/accountingentryimporterview.cpp
    gui/settingsdialog.cpp
    gui/memberlistdelegate.cpp

    dao/cashaccountdao.cpp
    dao/databasestructure.cpp
    dao/memberdao.cpp
    dao/balancedao.cpp
    dao/contributiondao.cpp

    accounting/balancepersister.cpp
    accounting/balanceentry.cpp
    accounting/statemententry.cpp
    accounting/contributionentry.cpp
    accounting/pay.cpp

    member.cpp
    )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

# Die ui_xxxx.h files werden im CMAKE_CURRENT_BINARY_DIR erzeugt.
if(${QT5})
    qt5_wrap_ui(UI_OUTFILES ${QT_UI})
else(${QT5})
    qt4_wrap_ui(UI_OUTFILES ${QT_UI})
endif(${QT5})

add_library(memberManagerLib STATIC ${QT_SRCS} ${MOC_OUTFILES} ${UI_OUTFILES})
if(${QT5})
    target_link_libraries(memberManagerLib Qt5::Widgets Qt5::Sql)
endif(${QT5})

add_executable(memberManager main.cpp)

if(${QT5})
    target_link_libraries(memberManager memberManagerLib ${QIABANKING_LIBRARIES} ${AQB_LIBRARIES} ${GWN_LIBRARIES} Qt5::Widgets Qt5::Sql)
else(${QT5})
    target_link_libraries(memberManager memberManagerLib ${QT_LIBRARIES} ${QIABANKING_LIBRARIES} ${AQB_LIBRARIES} ${GWN_LIBRARIES})
endif(${QT5})
