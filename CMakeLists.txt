cmake_minimum_required (VERSION 3.23)

project (triangle_intersection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_UNITTESTS  "Build unit tests. Googletest is reguired" ON)
option(BUILD_EXECUTABLE "Build cli executable"                     ON)

set(INSTALL_INCLUDES_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_LIBS_DIR     ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_TESTS_DIR    ${CMAKE_INSTALL_PREFIX}/tests)
set(INSTALL_EXE_DIR      ${CMAKE_INSTALL_PREFIX}/bin)
set(TARGET_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXAMPLES_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/examples)

add_subdirectory(src)

if(BUILD_UNITTESTS)
  message(STATUS "Build unit tests is ON")
  enable_testing()
  find_package(GTest REQUIRED)
  add_subdirectory(tests)
  include(GoogleTest)
endif()
