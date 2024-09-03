
message(STATUS "Configuring unit tests")

set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)

set(GTEST_LINK_LIBS 
  ${GTEST_BOTH_LIBRARIES}
)

if(UNIX)
  set(PTHREAD_LIB
    pthread
  )
elseif(WIN32)
  set(PTHREAD_LIB)
endif()

macro(configure_test TEST_NAME SRC_FILE)
  message(STATUS "Configuring ${TEST_NAME}")

  add_executable(${TEST_NAME} ${SRC_FILE})
  set(LINK_LIBS ${ARGN}) # libs for target_link_libraries
  message("Libraries linked to '${TEST_NAME}' test: ${LINK_LIBS}")
  target_include_directories(${TEST_NAME} 
    PUBLIC 
      ${GTEST_INCLUDE_DIRS}
      ${TARGET_INCLUDE_DIR}
  )
  
  target_link_libraries(${TEST_NAME}
    PUBLIC
      ${LINK_LIBS}
      ${GTEST_BOTH_LIBRARIES}
      ${PTHREAD_LIB}
  )

  gtest_discover_tests(${TEST_NAME} WORKING_DIRECTORY ${INSTALL_TESTS_DIR})
  install(TARGETS ${TEST_NAME} DESTINATION ${INSTALL_TESTS_DIR})

  message(STATUS "Configuring ${TEST_NAME} - Done")
endmacro()

configure_test(test-geometry test_geometry.cpp ti-geometry)
configure_test(test-algorithms test_algorithms.cpp ti-geometry ti-algorithms)
configure_test(test-io test_io.cpp ti-geometry ti-io)

message(STATUS "Configuring unit tests - Done")
