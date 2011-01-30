
configure_file (
  "${PROJECT_SOURCE_DIR}/TestConfig.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/TestConfig.h"
  )

include_directories(../)

qt4_add_test(memberDetailModel MemberDetailModelTest.cpp)
qt4_add_test(memberFilter MemberFilterTest.cpp)
qt4_add_test(memberModel MemberModelTest.cpp)
qt4_add_test(member MemberTest.cpp)
qt4_add_test(contributionModel ContributionModelTest.cpp)
qt4_add_test(kassaModel KassaModelTest.cpp)
qt4_add_test(saldoSumModel SaldoSumModelTest.cpp)
qt4_add_test(saldoModel SaldoModelTest.cpp)
qt4_add_test(memberDao MemberDaoTest.cpp)
