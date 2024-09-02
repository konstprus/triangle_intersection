cmake_minimum_required (VERSION 3.16)

project (triangle_intersection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_UNITTESTS  "Build unitests. Googletest is reguired" ON)
option(BUILD_EXECUTABLE "Build cli executable"                   ON)

set(INSTALL_INCLUDES_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(INSTALL_LIBS_DIR     ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_TESTS_DIR    ${CMAKE_INSTALL_PREFIX}/tests)
set(INSTALL_EXE_DIR      ${CMAKE_INSTALL_PREFIX}/bin)
set(TARGET_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR})

set(LIB_GEOMETRY_HDR_FILES 
  base3d.h
  point3d.h
  vector3d.h
  segment3d.h
  triangle3d.h
)

set(LIB_GEOMETRY_SRC_FILES 
  base3d.cpp
  point3d.cpp
  vector3d.cpp
  segment3d.cpp
  triangle3d.cpp
)

add_library(ti-geometry STATIC 
  ${LIB_GEOMETRY_HDR_FILES}
  ${LIB_GEOMETRY_SRC_FILES}
)

set(LIB_ALGORITHMS_HDR_FILES
  intersection_algorithms.h
)

set(LIG_ALGORITHMS_SRC_FILES
  intersection_algorithms.cpp
)

add_library(ti-algorithms STATIC 
  ${LIB_ALGORITHMS_HDR_FILES}
  ${LIG_ALGORITHMS_SRC_FILES}
)
target_link_libraries(ti-algorithms PRIVATE ti-geometry)

set(LIB_IO_HDR_FILES
  geometry_io.h
)

set(LIG_IO_SRC_FILES
  geometry_io.cpp
)

add_library(ti-io STATIC 
  ${LIB_IO_HDR_FILES}
  ${LIG_IO_SRC_FILES}
)
target_link_libraries(ti-algorithms PRIVATE ti-geometry)


if(BUILD_EXECUTABLE)
  add_executable(ti-checker main.cpp)
  target_link_libraries(ti-checker PRIVATE ti-geometry ti-algorithms ti-io)
endif()

if(BUILD_UNITTESTS)
  find_package(GTest REQUIRED)
  enable_testing()
  add_subdirectory(tests)
  include(GoogleTest)
endif()

set(INSTALL_LIBS 
  ti-geometry 
  ti-algorithms 
  ti-io
)

set(INSTALL_HDR_FILES 
  ${LIB_GEOMETRY_HDR_FILES} 
  ${LIB_ALGORITHMS_HDR_FILES} 
  ${LIB_IO_HDR_FILES}
)

install(TARGETS ${INSTALL_LIBS} LIBRARY DESTINATION ${INSTALL_LIBS_DIR})
install(FILES ${INSTALL_HDR_FILES} DESTINATION ${INSTALL_INCLUDES_DIR})
if(BUILD_EXECUTABLE)
  install(TARGETS ti-checker DESTINATION ${INSTALL_EXE_DIR})
endif()
