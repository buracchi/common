add_library(concurrency-rwfslock "src/rwfslock.c")
target_include_directories(concurrency-rwfslock PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")
target_link_libraries(concurrency-rwfslock PRIVATE containers-linked-list-map)
target_link_libraries(concurrency-rwfslock PRIVATE pthread)
target_link_libraries(concurrency-rwfslock PRIVATE utilities-misc)
target_link_libraries(concurrency-rwfslock PRIVATE utilities-try)
target_link_libraries(concurrency-rwfslock INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()
