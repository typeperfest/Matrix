set(cmake_minimum_required 3.26)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

project(playground)

add_library(IntMatrix STATIC lib/IntMatrix.cpp)

add_executable(main src/main.cpp)