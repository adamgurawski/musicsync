cmake_minimum_required(VERSION 3.10)

project(musicsync)

add_executable(musicsync main.cpp "filename_extractor.cpp" "filename_parser.cpp" "song_extractor.hpp" "song_extractor.cpp")

set_property(TARGET musicsync PROPERTY CXX_STANDARD 17)
