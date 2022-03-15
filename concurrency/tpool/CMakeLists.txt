add_library(concurrency-tpool "src/tpool.c")
target_include_directories(concurrency-tpool PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(concurrency-tpool PRIVATE containers-double-linked-list-stack-queue)
target_link_libraries(concurrency-tpool PRIVATE pthread)
target_link_libraries(concurrency-tpool PRIVATE utilities-misc)
target_link_libraries(concurrency-tpool PRIVATE utilities-try)
target_link_libraries(concurrency-tpool INTERFACE coverage_config)
set_target_properties(concurrency-tpool PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()
