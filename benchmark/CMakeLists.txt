cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(IntMatrixBench)

add_library(IntMatrixSSE STATIC ../lib/IntMatrix.cpp)
add_library(IntMatrix STATIC ../lib/IntMatrix.cpp)

target_compile_definitions(IntMatrixSSE PUBLIC "SIMD_EXTENSION_ENABLED")

# With SSE, with O3
add_executable(benchSSE_O3 main.cpp)
target_compile_options(benchSSE_O3 PRIVATE "-O3")
target_compile_definitions(benchSSE_O3 PRIVATE "O3_ENABLED")
target_link_libraries(benchSSE_O3 IntMatrixSSE)

# Without SSE, with O3
add_executable(benchO3 main.cpp)
target_compile_options(benchO3 PRIVATE "-O3")
target_compile_definitions(benchO3 PRIVATE "O3_ENABLED")
target_link_libraries(benchO3 IntMatrix)

# Without SSE, without O3
add_executable(bench main.cpp)
target_link_libraries(bench IntMatrix)

