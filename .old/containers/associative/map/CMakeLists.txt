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

add_library(
	"list_map"
	"list_map.c"
	"list_map.h"
	)

target_include_directories("list_map" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options("list_map" PUBLIC -Wall -pedantic)
target_link_libraries("list_map" PUBLIC coverage_config)
target_link_libraries("list_map" PRIVATE "list")
target_link_libraries("list_map" PRIVATE "iterators")
target_link_libraries("list_map" PRIVATE "double_linked_list")
target_link_libraries("list_map" PRIVATE "pair")
