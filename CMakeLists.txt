cmake_minimum_required(VERSION 3.0.0)

project(root)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#[==[
find_package(Boost 1.40 REQUIRED COMPONENTS json)

]==]

add_subdirectory(src)
