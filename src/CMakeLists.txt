add_subdirectory(maze)
target_include_directories(maze PUBLIC .)

add_subdirectory(graphics)
target_include_directories(graphics PUBLIC .)

add_subdirectory(game)
target_include_directories(game PUBLIC .)

target_include_directories(testing_glfw PUBLIC ../external/glfw/include)
target_link_directories(testing_glfw PRIVATE ../external/glfw/src)
