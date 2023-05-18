cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(IntMatrix)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

if (BUILD_X86_WITH_SSE OR BUILD_BENCHMARK)
    add_library(IntMatrixSSE STATIC src/IntMatrix.cpp)
    target_compile_definitions(IntMatrixSSE PUBLIC "SIMD_EXTENSION_ENABLED")
endif()

add_library(IntMatrix STATIC src/IntMatrix.cpp)

add_library(IntMatrixO3 STATIC src/IntMatrix.cpp)
target_compile_options(IntMatrixO3 PUBLIC "-O3")

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wshadow")

if(BUILD_BENCHMARK)
    include(benchmark/benchmark.cmake)
endif()

if (BUILD_TESTS)
    enable_testing()
    add_executable(
        tests
        tests/test.cpp
    )
    if (BUILD_X86_WITH_SSE)
        target_link_libraries(
            tests
            GTest::gtest_main
            IntMatrixSSE
        )
    else()
        target_link_libraries(
            tests
            GTest::gtest_main
            IntMatrix
        )
    endif()
    include(GoogleTest)
    gtest_discover_tests(tests)
endif()

