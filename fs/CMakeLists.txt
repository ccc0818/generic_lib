cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 11)

project(fs)

add_library(fs SHARED fs.c)
