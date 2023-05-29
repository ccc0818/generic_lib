cmake_minimum_required(VERSION 3.20)

project(demo)

add_executable(demo main.c)
target_include_directories(demo PRIVATE ${CMAKE_SOURCE_DIR}/fs)
target_link_libraries(demo fs)
