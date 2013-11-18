
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

    accounting/memberdebt.cpp
    accounting/memberaccountingdata.cpp
    accounting/contributionreceiptparser.cpp

    gui/mainwindowuicontroller.cpp
    gui/contributionreceipthandler.cpp
    gui/memberhandler.cpp
    gui/memberlisthandler.cpp
    gui/proxytablemodel.cpp
    gui/cashimporthandler.cpp
    gui/balancepersisthandler.cpp
    gui/feedebthandler.cpp

    databasemanager.cpp
    )

set(RESOURCES ../resources.qrc)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config.h"
  )

add_library(memberManagerLib STATIC ${QT_SRCS})
target_link_libraries(memberManagerLib Qt5::Widgets Qt5::Sql Qt5::Qml)

qt5_add_resources(QRC ${RESOURCES})
add_executable(memberManager main.cpp ${QRC})
target_link_libraries(memberManager memberManagerLib ${QDJ_LDFLAGS} Qt5::Core Qt5::Widgets Qt5::Qml Qt5::Quick)
