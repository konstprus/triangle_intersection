
set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

set(GTEST_LINK_LIBS 
  ${GTEST_BOTH_LIBRARIES}
)

if(UNIX)
message("DSDSDSD")
  set(GTEST_LINK_LIBS 
    ${GTEST_BOTH_LIBRARIES}
    pthread
  )
endif()

add_executable(test-geometry test_geometry.cpp)
target_include_directories(test-geometry 
  PUBLIC 
    ${GTEST_INCLUDE_DIRS}
    ${TARGET_INCLUDE_DIR}
)

set_target_properties(test-geometry PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(test-geometry
  PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    ti-geometry
)

gtest_discover_tests(test-geometry WORKING_DIRECTORY ${INSTALL_TESTS_DIR})
install(TARGETS test-geometry DESTINATION ${INSTALL_TESTS_DIR})

add_executable(test-algorithms test_algorithms.cpp)
target_include_directories(test-algorithms 
  PUBLIC
    ${GTEST_INCLUDE_DIRS}
    ${TARGET_INCLUDE_DIR}
)

set_target_properties(test-algorithms PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(test-algorithms
  PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    ti-geometry
    ti-algorithms
)

gtest_discover_tests(test-algorithms WORKING_DIRECTORY ${INSTALL_TESTS_DIR})
install(TARGETS test-algorithms DESTINATION ${INSTALL_TESTS_DIR})

add_executable(test-io test_io.cpp)
target_include_directories(test-io 
  PUBLIC
    ${GTEST_INCLUDE_DIRS}
    ${TARGET_INCLUDE_DIR}
)

set_target_properties(test-io PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(test-io
  PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    ti-geometry
    ti-io
)

gtest_discover_tests(test-io WORKING_DIRECTORY ${INSTALL_TESTS_DIR})
install(TARGETS test-io DESTINATION ${INSTALL_TESTS_DIR})


