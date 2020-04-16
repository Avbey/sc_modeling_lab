cmake_minimum_required(VERSION 3.15)
project(lab C)

set(CMAKE_C_STANDARD 99)

add_executable(lab main.c matrix.c matrix.h io_test.c io_test.h m_omp.c m_omp.h sequential.c sequential.h m_mpi.c test.c)

find_package(OpenMP)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")