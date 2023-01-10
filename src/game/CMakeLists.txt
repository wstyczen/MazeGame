add_library(game
  game.cpp
  maze.cpp
  difficulty.cpp
  settings.cpp
)

target_link_libraries(game
  PUBLIC maze
)
