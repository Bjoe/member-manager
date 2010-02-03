
set(BACKEND_MANAGEMENT_SRC
    Balance.cpp
    Bank.cpp
    Contribution.cpp
    EMail.cpp
    EMailException.cpp
    Member.cpp
    Ressourcen.cpp
    VillageSquare.cpp
    dorfmanagement.cpp
    dorfmanagementAddons.cpp
    )
    
# Setze sourcen fuer die tests
set(BACKEND_MANAGEMENT_SRC ${BACKEND_MANAGEMENT_SRC} PARENT_SCOPE)

add_executable(dorfverwaltung main.cc ${BACKEND_MANAGEMENT_SRC})
target_link_libraries(dorfverwaltung ${LITESQL_LIBRARIES} ${Boost_LIBRARIES})

