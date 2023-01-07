add_subdirectory(maze)
target_include_directories(maze PUBLIC .)

add_subdirectory(graphics)
target_include_directories(graphics PUBLIC .)

add_subdirectory(game)
target_include_directories(game PUBLIC .)

target_include_directories(graphics
  PUBLIC .
  PUBLIC ../external/glfw/include
  PUBLIC ../external/glad/include
  PUBLIC ../external/glm)
target_link_directories(graphics
  PUBLIC ../external/glfw/src
  PUBLIC ../external/glad/src)

