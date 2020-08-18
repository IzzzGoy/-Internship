cmake_minimum_required(VERSION 3.16)
project(DB)

set(CMAKE_CXX_STANDARD 17)

add_executable(DB main.cpp DataBase.cpp DataBase.h Entity.cpp Entity.h Table.cpp Table.h Row.cpp Row.h Integer.cpp Integer.h Double.cpp Double.h String.cpp String.h Date.cpp Date.h)