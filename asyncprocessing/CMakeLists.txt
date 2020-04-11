cmake_minimum_required(VERSION 3.13)
project(asyncprocessing)

set(CMAKE_CXX_STANDARD 11)


set(Boost_DEBUG OFF)
set(BOOST_ROOT /usr/local)

find_package(Boost 1.72 COMPONENTS filesystem)
#include_directories(${Boost_INCLUDE_DIR})

message(STATUS "Boost version: ${Boost_VERSION}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
message(STATUS "Boost includes: ${Boost_INCLUDE_DIR}")

add_executable(asyncprocessing main.cpp Generator.cpp Generator.h Inner.cpp Inner.h Outer.cpp Outer.h)
target_link_libraries(asyncprocessing ${Boost_LIBRARIES})
