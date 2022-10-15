cmake_minimum_required(VERSION 3.16)

add_library(compmath INTERFACE)
target_link_directories(compmath INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
