
find_package( Boost 1.39.0 COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

set(BACKEND_TEST_SRC
    BalanceTest.cpp
    BankTest.cpp
    ContributionTest.cpp
    EMailExceptionTest.cpp
    EMailTest.cpp
    MemberTest.cpp
    RessourcenTest.cpp
    TestFixture.cpp
    VillageSquareTest.cpp
    )

# Setze src Verzeichniss
foreach(_current ${BACKEND_MANAGEMENT_SRC})
    set(BACKEND_MANAGEMENT_SRC_DIR ${BACKEND_MANAGEMENT_SRC_DIR} ../src/${_current})
endforeach(_current ${BACKEND_MANAGEMENT_SRC})

add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(dorfverwaltungTest UnitTestMain.cpp ${BACKEND_TEST_SRC} ${BACKEND_MANAGEMENT_SRC_DIR})
target_link_libraries(dorfverwaltungTest ${LITESQL_LIBRARIES} ${Boost_LIBRARIES})

add_test(dorfverwaltungTest dorfverwaltungTest)

