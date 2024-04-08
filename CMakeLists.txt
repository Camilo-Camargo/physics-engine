cmake_minimum_required(VERSION 3.29.1)

project(PhysicsEngine)

# Neovim LSP helping
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(PhysicsEngine main.c main.h)

# C99 version
set_property(TARGET PhysicsEngine PROPERTY C_STANDARD 99)

target_link_libraries(PhysicsEngine ${SDL2_LIBRARIES})
