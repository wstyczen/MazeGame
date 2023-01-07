add_executable(example_test
  example_test.cpp
)

target_link_libraries(example_test
  maze
  gtest
  gmock
)
