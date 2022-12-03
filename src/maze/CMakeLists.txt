add_library(maze
  generators/aldous_broder_generator.cpp
  generators/hunt_and_kill_generator.cpp
  generators/ellers_generator.cpp
  generators/generator_factory.cpp
  generators/growing_tree_generator.cpp
  generators/kruskals_generator.cpp
  generators/prims_generator.cpp
  generators/recursive_backtracking_generator.cpp
  generators/sidewinder_generator.cpp
  generators/wilsons_generator.cpp
  generators/recursive_division_generator.cpp
  layout.cpp
  layout.hpp
  predecessors.cpp
  solvers/a_star_solver.cpp
  solvers/breadth_first_search_solver.cpp
  solvers/djikstra_solver.cpp
  solvers/solver_factory.cpp
  solvers/solver.cpp
  unvisited.cpp
  utility.cpp
)

target_link_libraries(maze
  Boost::json
)

add_executable(maze_test
  generator_test_run.cpp
  launch.cpp
)

target_link_libraries(maze_test
  maze
)
