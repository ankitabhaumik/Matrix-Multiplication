cmake_minimum_required (VERSION 3.3) #atleast 3.2 version or higher should be supported
project (matrix_multiply_proj) #project name

set(CMAKE_CXX_STANDARD 17) #atleast this much version of cpp compiler should support
SET(CMAKE_CXX_STANDARD_REQUIRED True) # if we dont have 17 or above version then dont compile


set(SOURCES
main.cpp) #add the sources file here and name it and use the name in executable.

#include_directories(include Customer/include) #it will tell the compiler to check the include the diretories  it work for alll the rpjects

add_executable(matrix_multiply ${SOURCES})