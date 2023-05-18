cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

project(IntMatrixBench)

# With custom SSE, without O3
add_executable(benchSSE ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/main.cpp)
target_link_libraries(benchSSE IntMatrixSSE)

# Without custom SSE, with O3
add_executable(benchO3 ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/main.cpp)
target_compile_definitions(benchO3 PRIVATE "O3_ENABLED")
target_link_libraries(benchO3 IntMatrixO3)

# Without custom SSE, without O3
add_executable(bench ${CMAKE_CURRENT_SOURCE_DIR}/benchmark/main.cpp)
target_link_libraries(bench IntMatrix)

