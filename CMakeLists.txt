cmake_minimum_required(VERSION 3.26)
project(lo21_splendor_duel)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lo21_splendor_duel
        main.cpp
        main.h
        classes/privilege.h
        classes/privilege.cpp)
