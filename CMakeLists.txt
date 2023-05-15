cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(playground)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_library(IntMatrix STATIC lib/IntMatrix.cpp)

string(APPEND CMAKE_CXX_FLAGS " -Wall")
if (BUILD_X86_WITH_SSE)
    string(APPEND CMAKE_CXX_FLAGS " -D SIMD_EXTENSION_ENABLED")
endif()

add_executable(main src/main.cpp)

# Add testing features
enable_testing()
add_executable(
    tests
    tests/test.cpp
)
target_link_libraries(
    tests
    GTest::gtest_main
    IntMatrix
)
include(GoogleTest)
gtest_discover_tests(tests)