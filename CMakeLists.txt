cmake_minimum_required(VERSION 3.10)

project(musicsync)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_executable(musicsync ${SOURCES})
set_property(TARGET musicsync PROPERTY CXX_STANDARD 17)
