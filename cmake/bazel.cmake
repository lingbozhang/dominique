# This file contains cmake functions that support bazel-like syntax
cmake_minimum_required(VERSION 3.13)

# cc_binary for build an executable target:
# cc_binary(
#  <NAME>
#  <SRCS>...
#  <HDRS>...
#  <DEPS>...
#)
function(cc_binary)
  set(options "")
  set(oneValueArgs NAME)
  set(multiValueArgs SRCS HDRS DEPS)
  cmake_parse_arguments(
    CC_BINARY
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
  )
  if(NOT CC_BINARY_NAME)
    message(FATAL_ERROR "Library name is not specified")
  endif()
  if(NOT CC_BINARY_SRCS)
    message(FATAL_ERROR "Source files are not specified for target: 
        ${CC_BINARY_NAME}")
  endif()
  add_executable(${CC_BINARY_NAME} ${CC_BINARY_SRCS} ${CC_BINARY_HDRS})
  if(CC_BINARY_DEPS) 
    target_link_libraries(
      ${CC_BINARY_NAME}
     PRIVATE
      ${CC_BINARY_DEPS}
  )
  endif()
  set_target_properties(${CC_BINARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)
endfunction()

# cc_library for build a library:
# cc_library(
#  [STATIC|SHARED]
#  <NAME>
#  <SRCS>...
#  <HDRS>...
#  <DEPS>...
#  <PUBLIC_DEPS>...
#)
function(cc_library)
  set(options STATIC SHARED)
  set(oneValueArgs NAME)
  set(multiValueArgs SRCS HDRS DEPS PUBLIC_DEPS)
  cmake_parse_arguments(
    CC_LIBRARY
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
  )

  if(NOT CC_LIBRARY_NAME)
    message(FATAL_ERROR "Library name is not specified")
  endif()

  if(NOT CC_LIBRARY_SRCS)
    message(FATAL_ERROR "Source files are not specified for target: 
        ${CC_LIBRARY_NAME}")
  endif()

  if(CC_LIBRARY_STATIC)
    add_library(${CC_LIBRARY_NAME} STATIC ${CC_LIBRARY_SRCS} ${CC_LIBRARY_HDRS})
  elseif(CC_LIBRARY_SHARED)
    add_library(${CC_LIBRARY_NAME} SHARED ${CC_LIBRARY_SRCS} ${CC_LIBRARY_HDRS})
  else()
    add_library(${CC_LIBRARY_NAME} ${CC_LIBRARY_SRCS} ${CC_LIBRARY_HDRS})
  endif()

  if(CC_LIBRARY_DEPS) 
    target_link_libraries(
      ${CC_LIBRARY_NAME}
     PRIVATE
      ${CC_LIBRARY_DEPS}
    )
  endif()
  if(CC_LIBRARY_PUBLIC_DEPS)
    target_link_libraries(
      ${CC_LIBRARY_NAME}
     PUBLIC
     ${CC_LIBRARY_PUBLIC_DEPS}
    )
  endif()

  set_target_properties(${CC_LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)
endfunction()
