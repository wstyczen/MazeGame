cmake_minimum_required(VERSION 3.0.0)

project(root)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Can interfere with debugging
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(src)
add_subdirectory(external/google_test)
