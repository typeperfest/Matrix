cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(IntMatrixBench)

add_library(IntMatrixSSE STATIC ../lib/IntMatrix.cpp)
add_library(IntMatrix STATIC ../lib/IntMatrix.cpp)

target_compile_definitions(IntMatrixSSE PUBLIC "SIMD_EXTENSION_ENABLED")

add_executable(benchSSE main_SSE.cpp)
target_link_libraries(benchSSE IntMatrixSSE)

add_executable(benchO3 main_O3.cpp)
target_compile_options(benchO3 PRIVATE "-O3")
target_link_libraries(benchO3 IntMatrix)
