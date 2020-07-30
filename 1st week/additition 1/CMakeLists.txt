cmake_minimum_required(VERSION 3.16)
project(additition_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(additition_1 main.cpp Node.h Value.cpp Value.h Variable.cpp Variable.h Operator.cpp Operator.h)