cmake_minimum_required(VERSION 3.16)
project(Chat)

set(CMAKE_CXX_STANDARD 20)

link_libraries(ws2_32)
add_executable(Chat main.cpp Server.cpp Server.h POJOUser.cpp POJOUser.h)
