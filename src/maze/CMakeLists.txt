add_executable(maze
  launch.cpp
  utility.cpp
  layout.hpp
  layout.cpp
  generator_factory.cpp
  kruskals_generator.cpp
  prims_generator.cpp
  recursive_backtracking_generator.cpp
  breadth_first_search_solver.cpp
  solver_factory.cpp
  solver.cpp
  unvisited.cpp
  growing_tree_generator.cpp
  aldous_broder_generator.cpp
  wilsons_generator.cpp
  generator_test_run.cpp
)

# target_link_libraries(launch
#   maze_generators)
