cmake_minimum_required(VERSION 3.10)

project(musicsync)

add_executable(musicsync main.cpp local_files_utils.cpp)

set_property(TARGET musicsync PROPERTY CXX_STANDARD 17)
