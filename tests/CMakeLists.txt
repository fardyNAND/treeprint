find_package(GTest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Conditional compilation of tests/main.cxx if it exists.
# Config provided as a way for raw tests.
# tests/main.cxx is blacklisted in .gitignore.
set(SCRATCH_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/main.cxx")
if(EXISTS "${SCRATCH_MAIN}")
  add_executable(treeprint_scratch
    ${SCRATCH_MAIN}
  )

  target_include_directories(treeprint_scratch PRIVATE
    ${CMAKE_SOURCE_DIR}/include
  )

  apply_loose_flags(treeprint_scratch)

  set_target_properties(treeprint_scratch PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
  )
endif()

add_executable(treeprint_tests
  test_set1.cxx
)

target_include_directories(treeprint_tests PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

apply_strict_flags(treeprint_tests)

target_link_libraries(treeprint_tests PRIVATE
  GTest::gtest_main
)

set_target_properties(treeprint_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

include(GoogleTest)
gtest_discover_tests(treeprint_tests
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
  PROPERTIES
    LABELS "unit"
)

