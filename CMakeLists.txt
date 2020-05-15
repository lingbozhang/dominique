cmake_minimum_required(VERSION 3.13)

project(Dominique LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
# Exports compilation database for VIM-LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Third party configurations
add_subdirectory(third_party/googletest)
enable_testing()
include(GoogleTest)
message(STATUS ${gtest_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src)
