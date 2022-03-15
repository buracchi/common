cmake_minimum_required (VERSION 3.8)

add_library(
	"list"
	"list.c"
	"list.h"
	)

target_include_directories("list" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options("list" PUBLIC -Wall -pedantic)
target_link_libraries("list" PUBLIC coverage_config)
target_link_libraries("list" PRIVATE "iterators")

add_library(
	"linked_list"
	"linked_list.c"
	"linked_list.h"
	)

target_include_directories("linked_list" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options("linked_list" PUBLIC -Wall -pedantic)
target_link_libraries("linked_list" PUBLIC coverage_config)
target_link_libraries("linked_list" PRIVATE "list")
target_link_libraries("linked_list" PRIVATE "iterators")

add_library(
	"double_linked_list"
	"double_linked_list.c"
	"double_linked_list.h"
	)

target_include_directories("double_linked_list" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options("double_linked_list" PUBLIC -Wall -pedantic)
target_link_libraries("double_linked_list" PUBLIC coverage_config)
target_link_libraries("double_linked_list" PRIVATE "list")
target_link_libraries("double_linked_list" PRIVATE "iterators")
