add_library(
        iterators
        STATIC
        "src/iterator.c"
)
target_compile_definitions(iterators PRIVATE ITERATORS_VERSION=1)
target_include_directories(iterators PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(iterators INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()
