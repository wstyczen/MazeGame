add_library(graphics
  shaders/shader.cpp
  shapes/complex_cube.cpp
  shapes/data_buffers/EBO.cpp
  shapes/data_buffers/VAO.cpp
  shapes/data_buffers/VBO.cpp
  shapes/digit_figure.cpp
  shapes/dynamic_solid_figure.cpp
  shapes/game_window.cpp
  shapes/maze_figure.cpp
  shapes/path_figure.cpp
  shapes/solid_figure.cpp
)

if (LINUX)
  set(glad_DIR "/opt/vcpkg/installed/x64-linux/share/glad")
  set(glm_DIR "/opt/vcpkg/installed/x64-linux/share/glm")
  set(glfw3_DIR "/opt/vcpkg/installed/x64-linux/share/glfw3")
else()
  set(glad_DIR "C:\\Cpp\\vcpkg\\installed\\x64-mingw-dynamic\\share\\glad")
  set(glm_DIR "C:\\Cpp\\vcpkg\\installed\\x64-mingw-dynamic\\share\\glm")
  set(glfw3_DIR "C:\\Cpp\\vcpkg\\installed\\x64-mingw-dynamic\\share\\glfw3")
endif()

find_package(glad CONFIG REQUIRED)
target_link_libraries(graphics PUBLIC glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(graphics PUBLIC glm::glm)

find_package(glfw3 CONFIG REQUIRED)
if(LINUX)
target_link_libraries(graphics PUBLIC glfw)
else()
target_link_libraries(graphics PUBLIC glfw3)
endif()

target_link_libraries(graphics
  PUBLIC game
)

add_executable(graphics_main_hello
  main_hello.cpp
)
target_link_libraries(graphics_main_hello
  graphics
  maze
  game
)
