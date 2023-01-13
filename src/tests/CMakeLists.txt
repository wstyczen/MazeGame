add_executable(tests
  run_all_tests.cpp
  maze/utility.cpp
  maze/layout.cpp
  maze/paths.cpp
  maze/solvers.cpp
  maze/generators.cpp
  game/difficulty.cpp
)

target_link_libraries(tests
  maze
  game
  gtest
  gmock
)
