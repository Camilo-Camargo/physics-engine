cmake_minimum_required(VERSION 3.29.1)
find_package(libwebsockets CONFIG REQUIRED)

project(PhysicsEngine)

# Neovim LSP helping
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(engine)

add_executable(PhysicsEngine main.c main.h)
add_executable(PhysicsEngineServer server.c)

# C99 version
set_property(TARGET PhysicsEngine PROPERTY C_STANDARD 99)

target_link_libraries(PhysicsEngine ${SDL2_LIBRARIES} websockets_shared ${LIBWEBSOCKETS_DEP_LIBS} engine)
target_link_libraries(PhysicsEngineServer websockets_shared ${LIBWEBSOCKETS_DEP_LIBS})

target_include_directories(engine PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/engine")
