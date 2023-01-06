cmake_minimum_required(VERSION 3.0.0)

project(root)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#[==[
find_package(Boost 1.40 REQUIRED COMPONENTS json)
]==]

add_subdirectory(src)
add_subdirectory(external/glfw)
