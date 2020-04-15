cmake_minimum_required(VERSION 3.13)
project(testing)

set(CMAKE_CXX_STANDARD 11)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
RESULT_VARIABLE result
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
RESULT_VARIABLE result
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
${CMAKE_CURRENT_BINARY_DIR}/googletest-build
EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(Boost_DEBUG OFF)
set(BOOST_ROOT /usr/local)

find_package(Boost 1.72 COMPONENTS filesystem)
#include_directories(${Boost_INCLUDE_DIR})

message(STATUS "Boost version: ${Boost_VERSION}")


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(testing GreetingTest.cpp Greeting.cpp Greeting.h BadRunningAverage.cpp BadRunningAverage.h GoodRunningAverage.h RunningAverageTest.cpp CompilationChecks.cpp DestructuringTest.cpp HorribleTricksTest.cpp BoostTidbitsTest.cpp SimpleCollectionsTest.cpp GreeterFunctionTest.cpp ScopesTest.cpp TypeDeterminationTest.cpp CopyAndMoveTest.cpp)
target_link_libraries(testing gtest_main ${Boost_LIBRARIES})
add_test(NAME silly_tests COMMAND testing)
