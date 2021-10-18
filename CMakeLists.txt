cmake_minimum_required(VERSION 3.17)
project(musicsync)
set(CMAKE_CXX_STANDARD 17)

add_executable(musicsync ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Specify sources for the project.
target_sources(musicsync PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/main.cpp
  ${CMAKE_SOURCE_DIR}/src/database.cpp
  ${CMAKE_SOURCE_DIR}/src/local_files_utils.cpp
  ${CMAKE_SOURCE_DIR}/src/songs_table_view.cpp
  ${CMAKE_SOURCE_DIR}/src/view.cpp)

# Specify include directories for the project.
target_include_directories(musicsync PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/sqlite)

#set_target_properties(musicsync PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# TODO: AG: It moves musicsync binaries to bin but also moves some gmockd.dll, gtestd.dll etc.
# which are not needed there - I assume these come from some library unit tests.
set_target_properties(musicsync PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Use a pre-built sqlite. Copy the dll so it's in the same directory as the executable.
file(COPY "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.dll" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Import SQLite library.
add_library(sqlite SHARED IMPORTED)
set_target_properties(sqlite PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.dll")
set_target_properties(sqlite PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/sqlite/sqlite3.lib")

# Import cpr library.
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG f4622efcb59d84071ae11404ae61bd821c1c344b) # the commit hash for 1.6.2
FetchContent_MakeAvailable(cpr)

target_link_libraries(musicsync PRIVATE sqlite cpr::cpr)
