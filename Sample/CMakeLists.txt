cmake_minimum_required(VERSION 3.25)
project(Sample CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(Sample Sample.cpp)

target_link_libraries(Sample PUBLIC Platinum)
target_include_directories(Sample PUBLIC ../Platinum)