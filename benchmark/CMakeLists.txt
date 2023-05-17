cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(IntMatrixBench)

add_library(IntMatrixSSE STATIC ../lib/IntMatrix.cpp)
add_library(IntMatrix STATIC ../lib/IntMatrix.cpp)

add_executable(benchSSE main_SSE.cpp)
target_compile_definitions(benchSSE PUBLIC "SIMD_EXTENSION_ENABLED")
target_link_libraries(benchSSE IntMatrixSSE)

add_executable(bench03 main_O3.cpp)
target_compile_options(bench03 PRIVATE "-O3")
target_link_libraries(bench03 IntMatrix)


