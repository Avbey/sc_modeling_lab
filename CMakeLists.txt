cmake_minimum_required(VERSION 3.15)
project(lab/src C)

set(CMAKE_C_STANDARD 99)

add_executable(lab src/main.c src/matrix.c src/matrix.h src/io_test.c src/io_test.h src/m_omp.c src/m_omp.h src/sequential.c src/sequential.h src/m_mpi.c)

find_package(OpenMP)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")