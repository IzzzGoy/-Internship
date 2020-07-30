cmake_minimum_required(VERSION 3.16)
project(4)

set(CMAKE_CXX_STANDARD 14)

add_executable(4 main.cpp Node.cpp Node.h Value.cpp Value.h Operation.cpp Operation.h Border.cpp Border.h Bracket.cpp Bracket.h)