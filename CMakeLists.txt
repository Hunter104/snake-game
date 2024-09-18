cmake_minimum_required(VERSION 3.10)
project(snake_game VERSION 1.0)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

FILE(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(snake_game ${SRCS})

target_link_libraries(snake_game raylib)
target_include_directories(snake_game PRIVATE include)

if (APPLE)
    target_link_libraries(snake_game "-framework IOKit")
    target_link_libraries(snake_game "-framework Cocoa")
    target_link_libraries(snake_game "-framework OpenGL")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "RELEASE")
  target_compile_definitions(snake_game PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
else()
  target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets")
endif()
