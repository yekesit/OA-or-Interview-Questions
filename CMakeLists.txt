cmake_minimum_required(VERSION 3.13)
project(OA-or-Interview-Question)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(amazon)
add_subdirectory(ea)
add_subdirectory(uber_ATG)
add_subdirectory(C3)
add_subdirectory(yelp)

add_executable(OA-or-Interview-Question main.cpp)
