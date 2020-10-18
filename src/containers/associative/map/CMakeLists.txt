cmake_minimum_required (VERSION 3.8)

add_library(
	"map"
	"map.c"
	"map.h"
	)

target_include_directories("map" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options("map" PUBLIC -Wall -pedantic)
target_link_libraries("map" PUBLIC coverage_config)
target_link_libraries("map" PRIVATE "iterators")
