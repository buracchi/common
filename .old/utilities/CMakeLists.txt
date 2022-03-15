cmake_minimum_required (VERSION 3.8)

add_library(
	"pair"
	"pair.h"
	"pair.c"
	)

target_include_directories("pair" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options("pair" PUBLIC -Wall -pedantic)
target_link_libraries("pair" PUBLIC coverage_config)
