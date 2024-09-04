
message(STATUS "Configuring ti-geometry lib")
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
message(STATUS "Configuring ti-geometry lib - Done")

message(STATUS "Configuring ti-algorithms lib")
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
target_link_libraries(ti-algorithms PUBLIC ti-geometry)
message(STATUS "Configuring ti-algorithms lib - Done")

message(STATUS "Configuring ti-io lib")
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
target_link_libraries(ti-io PUBLIC ti-geometry)
message(STATUS "Configuring ti-io lib - Done")

if(BUILD_EXECUTABLE)
  message(STATUS "Configuring ti-checker executable")
  add_executable(ti-checker main.cpp)
  target_link_libraries(ti-checker PRIVATE ti-geometry ti-algorithms ti-io)
  message(STATUS "Configuring ti-checker executable - Done")
endif()

set(INSTALL_HDR_FILES 
  ${LIB_GEOMETRY_HDR_FILES} 
  ${LIB_ALGORITHMS_HDR_FILES} 
  ${LIB_IO_HDR_FILES}
)

install(TARGETS ${INSTALL_LIBS} LIBRARY DESTINATION ${INSTALL_LIBS_DIR})
install(FILES ${INSTALL_HDR_FILES} DESTINATION ${INSTALL_INCLUDES_DIR})
if(BUILD_EXECUTABLE)
  install(TARGETS ti-checker DESTINATION ${INSTALL_EXE_DIR})
  install(DIRECTORY ${EXAMPLES_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()
