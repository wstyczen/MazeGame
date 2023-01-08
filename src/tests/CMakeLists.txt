add_executable(tests
  run_all_tests.cpp
  maze/utility.cpp
  maze/layout.cpp
  maze/paths.cpp
  maze/solvers.cpp
  maze/generators.cpp
)

target_link_libraries(tests
  maze
  gtest
  gmock
)
