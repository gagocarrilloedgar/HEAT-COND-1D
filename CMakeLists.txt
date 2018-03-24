
cmake_minimum_required(VERSION 2.8.12.2)
project ( CAS1)

set (CMAKE_C_COMPILER gcc)

file (GLOB SOURCES "./*.c")

add_executable (main ${SOURCES})

