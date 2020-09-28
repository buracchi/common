cmake_minimum_required (VERSION 3.8)

# add_subdirectory("abstract")

add_executable (
	example
	"main.c"
	"list/linked_list.c"
	)

target_include_directories(example PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

# target_link_libraries(example PRIVATE "abstract")
