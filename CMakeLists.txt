set(cmake_minimum_required 3.14)
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

add_executable(main src/main.cpp)

# Add testing features
enable_testing()
add_executable(
    test
    tests/test.cpp
)
target_link_libraries(
    test
    GTest::gtest_main
    IntMatrix
)
include(GoogleTest)
gtest_discover_tests(test)