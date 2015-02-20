cmake_minimum_required(VERSION 2.8.4)
project(Futoshiki)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -W -std=c99 -pedantic -I.")
set(SOURCE_FILES main.c)
add_executable(Futoshiki.out ${SOURCE_FILES})