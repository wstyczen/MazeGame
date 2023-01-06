# add_library(graphics
# hellocmake.cpp
# hellocmake.h
# shaders/shader.cpp
# shapes/data_buffers/EBO.cpp
# shapes/data_buffers/VBO.cpp
# shapes/data_buffers/VAO.cpp
# shapes/solid_figure.cpp
# shapes/dynamic_solid_figure.cpp
# shapes/dynamic_state_figure.cpp
# shapes/pawn_figure.cpp
# shapes/complex_cube.cpp
# shapes/maze_figure.cpp

# )


# set(glad_DIR "/opt/vcpkg/installed/x64-linux/share/glad")
# set(glm_DIR "/opt/vcpkg/installed/x64-linux/share/glm")
# set(glfw3_DIR "/opt/vcpkg/installed/x64-linux/share/glfw3")


# find_package(glad CONFIG REQUIRED)
# target_link_libraries(graphics PUBLIC glad::glad)

# find_package(glm CONFIG REQUIRED)
# target_link_libraries(graphics PUBLIC glm::glm)

# find_package(glfw3 CONFIG REQUIRED)
# target_link_libraries(graphics PUBLIC glfw)

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.vert
#      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/default.frag
#      DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# add_executable(graphics_test
#   main_hello.cpp
# )

# target_link_libraries(graphics_test
#   graphics
# )

