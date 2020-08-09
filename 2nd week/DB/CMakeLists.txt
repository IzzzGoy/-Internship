cmake_minimum_required(VERSION 3.16)
project(DB)

set(CMAKE_CXX_STANDARD 14)

add_executable(DB main.cpp DataBase.cpp DataBase.h Entity.cpp Entity.h Table.cpp Table.h Row.cpp Row.h)