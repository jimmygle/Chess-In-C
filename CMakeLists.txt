cmake_minimum_required(VERSION 3.6)
project(Chess_In_C)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        chess.c)

add_executable(Chess_In_C ${SOURCE_FILES})