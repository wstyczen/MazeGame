find_package(Boost 1.80.0 REQUIRED COMPONENTS system json regex)

add_library(maze_generators
  generator.hpp
  generator_factory.cpp
  generator_factory.hpp
  kruskals_generator.cpp
  kruskals_generator.hpp
  layout.cpp
  layout.hpp
)

target_link_libraries(maze_generators
  Boost::json
)

# target_include_directories(maze_generators PRIVATE ./src/utility)

