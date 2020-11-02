cmake_minimum_required(VERSION 3.17)
project(musicsync)
set(CMAKE_CXX_STANDARD 17)

add_executable(musicsync ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Specify sources for the project.
target_sources(musicsync PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/view.cpp
  ${CMAKE_SOURCE_DIR}/src/local_files_utils.cpp)

# Specify include directories for the project.
target_include_directories(musicsync PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/sqlite)

# Import SQLite library.
add_library(sqlite SHARED IMPORTED)
set_target_properties(sqlite PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.dll")
set_target_properties(sqlite PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.lib")

# Copy dll so it's in the same directory as the executable.
file(COPY "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.dll" DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(musicsync sqlite)
