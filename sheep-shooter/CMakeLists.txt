cmake_minimum_required(VERSION 3.10)

project(SheepShooter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-lSDL2 -lSDL2main")

add_library(engine engine/engine.cpp)
add_library(game::engine ALIAS engine)
target_include_directories(engine 
            PUBLIC engine/include
            PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_directories(engine PRIVATE SDL2 SDL2main)

add_executable(main src/main.cpp)

target_link_libraries(main game::engine)
