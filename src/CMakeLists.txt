
set(QT_MOC_HEADERS
    Gui/MainWindow.h
    Gui/MemberDialog.h
    Gui/ConnectionDialog.h
    Gui/SaldoDialog.h
    Gui/SaldoSumDialog.h
    Gui/ContributionDialog.h
    Gui/SummaryWindow.h

    CountMemberSummary.h
    CashSumSummary.h
    DebitSumSummary.h
    )

set(QT_UI
    Gui/mainWindow.ui
    Gui/memberDialog.ui
    Gui/ConnectionDialog.ui
    Gui/SaldoDialog.ui
    Gui/SaldoSumDialog.ui
    Gui/ContributionDialog.ui
    Gui/SummaryWindow.ui
    )

set(QT_SRCS
    Gui/MainWindow.cpp
    Gui/MemberDialog.cpp
    Gui/ConnectionDialog.cpp
    Gui/SaldoDialog.cpp
    Gui/SaldoSumDialog.cpp
    Gui/ContributionDialog.cpp
    Gui/SummaryWindow.cpp

    Model/MemberModel.cpp
    Model/KassaModel.cpp
    Model/SaldoModel.cpp
    Model/SaldoSumModel.cpp
    Model/ContributionModel.cpp
    Model/MemberDetailModel.cpp
    Model/MemberFilter.cpp
    Model/Member.cpp
    Model/DatabaseStructure.cpp

    SummaryHandler.cpp
    CountMemberSummary.cpp
    CashSumSummary.cpp
    DebitSumSummary.cpp
    )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Config.h"
  )

qt4_wrap_cpp(MOC_OUTFILES ${QT_MOC_HEADERS})

# Die ui_xxxx.h files werden im CMAKE_CURRENT_BINARY_DIR erzeugt.
qt4_wrap_ui(UI_OUTFILES ${QT_UI})

include(${QT_USE_FILE})

add_library(memberManagerLib STATIC ${QT_SRCS} ${MOC_OUTFILES} ${UI_OUTFILES})

add_executable(memberManager main.cpp)

target_link_libraries(memberManager memberManagerLib ${QT_LIBRARIES})
