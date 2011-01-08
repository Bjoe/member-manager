
find_package(Qt4 4.5.2 COMPONENTS QtTest REQUIRED)
include(${QT_USE_FILE})

set(QT_FRONTEND_TEST_MOC_HEADERS
    MainWindowTest.h
    MemberDialogTest.h
    MemberModelTest.h
    KassaModelTest.h
    SaldoModelTest.h
    SaldoSumModelTest.h
    MemberDetailModelTest.h
    MemberFilterTest.h
    ConnectionDialogTest.h
    SaldoDialogTest.h
    SaldoSumDialogTest.h
    ContributionModelTest.h
    ContributionDialogTest.h
    SummaryWindowTest.h
    CountMemberSummaryTest.h
    DebitSumSummaryTest.h
    CashSumSummaryTest.h
    TriggerThread.h
    )

set(QT_FRONTEND_TEST
    DialogButtonBoxHandler.cpp
    TestData.cpp
    MainWindowTest.cpp
    MemberDialogTest.cpp
    MemberModelTest.cpp
    KassaModelTest.cpp
    SaldoModelTest.cpp
    SaldoSumModelTest.cpp
    MemberDetailModelTest.cpp
    MemberFilterTest.cpp
    ConnectionDialogTest.cpp
    SaldoDialogTest.cpp
    SaldoSumDialogTest.cpp
    ContributionModelTest.cpp
    ContributionDialogTest.cpp
    SummaryWindowTest.cpp
    CountMemberSummaryTest.cpp
    DebitSumSummaryTest.cpp
    CashSumSummaryTest.cpp
    TriggerThread.cpp
    SummaryHandlerMock.cpp
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


add_executable(Dorfverwaltung-GUI-Qt-Test main.cpp ${QT_FRONTEND_TEST} ${QT_FRONTEND_SRC_DIR} ${MOC_OUTFILES_TEST} ${UI_OUTFILES_TEST})
target_link_libraries(Dorfverwaltung-GUI-Qt-Test ${QT_LIBRARIES})

add_test(Dorfverwaltung-GUI-Qt-Test Dorfverwaltung-GUI-Qt-Test)
