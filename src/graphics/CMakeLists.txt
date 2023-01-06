add_library(graphics
  ../../external/glad/src/glad.c
  hellocmake.cpp
  hellocmake.h
  shaders/shader.cpp
  shapes/data_buffers/EBO.cpp
  shapes/data_buffers/VBO.cpp
  shapes/data_buffers/VAO.cpp
  shapes/solid_figure.cpp
  shapes/dynamic_solid_figure.cpp
  shapes/dynamic_state_figure.cpp
  shapes/pawn_figure.cpp
  shapes/complex_cube.cpp
  shapes/maze_figure.cpp
)

target_link_libraries(graphics
  PUBLIC glfw3
)

add_executable(graphics_test
  main_hello.cpp
)

target_link_libraries(graphics_test
  graphics
  glfw3
)

add_executable(testing_glfw test_main.cpp)
target_link_libraries(testing_glfw PUBLIC glfw3)
