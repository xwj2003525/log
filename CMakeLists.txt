find_package(Boost REQUIRED)

set(SRC
   common.cpp
   log.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(log STATIC ${SRC})
target_link_libraries(log ${Boost_LIBRARIES})
