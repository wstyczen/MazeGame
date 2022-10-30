add_subdirectory(generators)

add_executable(main
  main.cpp)

target_link_libraries(main
  maze_generators)
