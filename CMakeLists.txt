cmake_minimum_required(VERSION 3.10)

project(musicsync)

add_executable(musicsync main.cpp "file_manager.cpp")

set_property(TARGET musicsync PROPERTY CXX_STANDARD 17)
