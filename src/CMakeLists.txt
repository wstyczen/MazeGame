add_subdirectory(maze)
target_include_directories(maze PUBLIC .)
target_include_directories(maze_test_run PUBLIC .)

add_subdirectory(graphics)
target_include_directories(graphics
  PUBLIC .
  PUBLIC ../external/glfw/include
  PUBLIC ../external/glad/include
  PUBLIC ../external/glm)
target_link_directories(graphics
  PUBLIC ../external/glfw/src
  PUBLIC ../external/glad/src)

add_subdirectory(game)
target_include_directories(game PUBLIC .)

add_subdirectory(tests)
target_include_directories(tests
  PUBLIC .
  PUBLIC ../external/google_test/googletest/include
  PUBLIC ../external/google_test/googlemock/include)

