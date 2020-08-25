cmake_minimum_required(VERSION 3.16)
project(Client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS -static)

link_libraries(ws2_32)
add_executable(Client main.cpp Client.cpp Client.h)