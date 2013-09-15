
set(QT_UI
    gui/connectiondialog.ui
    gui/summaryview.ui
    gui/memberdebtview.ui
    gui/paymentview.ui
    gui/accountingentryimporterview.ui
    gui/settingsdialog.ui
    )

set(QT_SRCS

    dao/membertablemodel.cpp
    dao/bankaccounttablemodel.cpp
    dao/contributiontablemodel.cpp
    dao/balancetablemodel.cpp
    dao/cashaccounttablemodel.cpp

    entity/member.cpp
    entity/contribution.cpp
    entity/balance.cpp
    entity/cashaccount.cpp
    entity/bankaccount.cpp

    accounting/arithmetic.cpp
    accounting/memberdonationsum.cpp
    accounting/memberfeesum.cpp
    accounting/memberadditionalsum.cpp
    accounting/cashimporter.cpp

    gui/mainwindowuicontroller.cpp
    gui/contributionreceipthandler.cpp
    gui/memberhandler.cpp
    gui/proxytablemodel.cpp
    gui/summaryhandler.cpp
    gui/cashimporthandler.cpp
    gui/balancepersisthandler.cpp

    gui/connectiondialog.cpp
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
    databasemanager.cpp
    )

set(RESOURCES ../resources.qrc)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

# Die ui_xxxx.h files werden im CMAKE_CURRENT_BINARY_DIR erzeugt.
qt5_wrap_ui(UI_OUTFILES ${QT_UI})

add_library(memberManagerLib STATIC ${QT_SRCS} ${UI_OUTFILES})
target_link_libraries(memberManagerLib Qt5::Widgets Qt5::Sql Qt5::Qml)

qt5_add_resources(QRC ${RESOURCES})
add_executable(memberManager main.cpp ${QRC})
target_link_libraries(memberManager memberManagerLib ${QIABANKING_LIBRARIES} ${QDJ_LDFLAGS} ${AQB_LDFLAGS} ${GWN_LDFLAGS} Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick)
