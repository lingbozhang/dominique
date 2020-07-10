cmake_minimum_required(VERSION 3.13)

project(Dominique LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
# Exports compilation database for VIM-LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(LLVM REQUIRED CONFIG PATHS "/usr/local/Cellar/llvm/10.0.0_3/")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
# Now build our tools
add_executable(simple-example llvm_example.cc)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(simple-example ${llvm_libs})

# Third party configurations
add_subdirectory(third_party/googletest)
enable_testing()
include(GoogleTest)
message(STATUS ${gtest_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src)
