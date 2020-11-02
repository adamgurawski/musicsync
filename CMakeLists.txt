cmake_minimum_required(VERSION 3.17)
project(musicsync)
set(CMAKE_CXX_STANDARD 17)

message("-- Binary dir: ${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")

set(SQLITE_DIR ${CMAKE_SOURCE_DIR}/storage)
message ("-- SQLite dir: ${SQLITE_DIR}")

find_library(SQLITE_LIB sqlite3.lib HINTS ${SQLITE_DIR})
message ("-- SQLite_LIB: ${SQLITE_LIB}")

add_executable(musicsync ${SOURCES})

target_include_directories(musicsync PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                            ${SQLITE_DIR})

target_link_libraries(musicsync PUBLIC ${SQLITE_LIB})

install(TARGETS musicsync DESTINATION bin)
install(FILES ${SQLITE_DIR}/sqlite3.dll DESTINATION bin)


