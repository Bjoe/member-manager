
set(QT_MOC_HEADERS
    MainWindow.h
    MemberDialog.h
    ConnectionDialog.h
    SaldoDialog.h
    SaldoSumDialog.h
    ContributionDialog.h
    SummaryWindow.h
    CountMemberSummary.h
    CashSumSummary.h
    DebitSumSummary.h
    )

set(QT_UI
    mainWindow.ui
    memberDialog.ui
    ConnectionDialog.ui
    SaldoDialog.ui
    SaldoSumDialog.ui
    ContributionDialog.ui
    SummaryWindow.ui
    )

set(QT_SRCS
    MainWindow.cpp
    MemberDialog.cpp
    MemberModel.cpp
    KassaModel.cpp
    SaldoModel.cpp
    SaldoSumModel.cpp
    ContributionModel.cpp
    MemberDetailModel.cpp
    MemberFilter.cpp
    DatabaseStructure.cpp
    ConnectionDialog.cpp
    SaldoDialog.cpp
    SaldoSumDialog.cpp
    ContributionDialog.cpp
    SummaryWindow.cpp
    SummaryHandler.cpp
    CountMemberSummary.cpp
    CashSumSummary.cpp
    DebitSumSummary.cpp
    Member.cpp
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
