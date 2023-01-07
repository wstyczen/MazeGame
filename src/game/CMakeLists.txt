add_library(game
  game.cpp
  maze.cpp
  difficulty.cpp
)

target_link_libraries(game
  PUBLIC maze
)
