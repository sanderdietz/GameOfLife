cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(gameOfLife)

set(SOURCES
    src/main.cpp
    src/GameOfLife.cpp
    src/Grid.cpp
)

add_executable(GameOfLife ${SOURCES})

target_link_libraries(GameOfLife GL glfw)

target_include_directories(GameOfLife PRIVATE ${PROJECT_SOURCE_DIR}/include)