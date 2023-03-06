cmake_minimum_required(VERSION 3.1.0)

project(closest-pair VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(core)
add_subdirectory(ui)
add_subdirectory(console)