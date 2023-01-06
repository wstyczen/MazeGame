add_library(game
  game.cpp
)

target_link_libraries(game
  Boost::json
)

target_link_libraries(game
  maze
)
