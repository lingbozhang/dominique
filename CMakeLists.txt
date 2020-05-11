cmake_minimum_required(VERSION 3.13)

project(Dominique LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
# Exports compilation database for VIM-LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(googletest)
add_subdirectory(src)
