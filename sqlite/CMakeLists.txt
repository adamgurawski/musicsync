cmake_minimum_required(VERSION 3.17)
project(musicsync)

add_library(sqlite STATIC sqlite3.c)

install(TARGETS sqlite DESTINATION lib)
install(FILES sqlite3.h DESTINATION include)