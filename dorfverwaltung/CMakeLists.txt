
find_library(LITESQL_LIBRARIES litesql)
find_path(LITESQL_INCLUDE_DIR litesql.hpp)

find_package( Boost 1.39.0 COMPONENTS date_time regex)

include_directories(${LITESQL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(src-utf)

