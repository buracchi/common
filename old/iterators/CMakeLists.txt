cmake_minimum_required (VERSION 3.8)

add_library(
	iterators
	"iterator.c"
	"iterator.h"
	)

target_include_directories(iterators PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(iterators PUBLIC -Wall -pedantic)
target_link_libraries(iterators PUBLIC coverage_config)
