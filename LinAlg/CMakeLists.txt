cmake_minimum_required(VERSION 3.16)
file(GLOB_RECURSE src *.h *.hpp *.cpp *.c)
add_library(linalg ${src})
