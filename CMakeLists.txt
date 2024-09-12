cmake_minimum_required(VERSION 3.10)
project(snake_game VERSION 1.0)

find_package(raylib 5.0 REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
FILE(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(snake_game ${SRCS})

target_link_libraries(snake_game raylib)
target_include_directories(snake_game PRIVATE include)

if (APPLE)
    target_link_libraries(snake_game "-framework IOKit")
    target_link_libraries(snake_game "-framework Cocoa")
    target_link_libraries(snake_game "-framework OpenGL")
endif()
