cmake_minimum_required(VERSION 3.29)
project(conway_s_game_of_life)

set(CMAKE_CXX_STANDARD 20)

add_executable(conway_s_game_of_life main.cpp Grid.h CircularMatrix.h
        Game.cpp
        Game.h
        Renderer.h)