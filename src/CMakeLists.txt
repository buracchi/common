cmake_minimum_required (VERSION 3.8)

add_subdirectory("containers")
add_subdirectory("iterators")

add_executable (
	example
	"main.c"
	)

target_link_libraries(example PRIVATE "linked_list")
target_link_libraries(example PRIVATE "iterators")
