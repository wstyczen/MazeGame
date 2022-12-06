add_library(graphics
hellocmake.cpp
hellocmake.h)


set(glad_DIR "/opt/vcpkg/installed/x64-linux/share/glad")
set(glm_DIR "/opt/vcpkg/installed/x64-linux/share/glm")
set(glfw3_DIR "/opt/vcpkg/installed/x64-linux/share/glfw3")


find_package(glad CONFIG REQUIRED)
target_link_libraries(graphics PUBLIC glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(graphics PUBLIC glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(graphics PUBLIC glfw)



add_executable(graphics_test
  main_hello.cpp
)

target_link_libraries(graphics_test
  graphics
)

