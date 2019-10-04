cmake_minimum_required(VERSION 3.14)

file(GLOB_RECURSE PROJ_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE LIBFT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libft/*.c")

project(wolfv2 C)
set(CMAKE_C_STANDARD 99)

add_executable(wolfv2 ${PROJ_SOURCES} ${LIBFT_SOURCES} src/read_map.c src/read_map_helper.c)