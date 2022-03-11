add_library(concurrency-tpool
    "src/tpool.c")

add_library(${PROJECT_NAMESPACE}::concurrency::tpool ALIAS concurrency-tpool)

target_include_directories(concurrency-tpool PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(concurrency-tpool PRIVATE containers-double-linked-list-stack-queue)
target_link_libraries(concurrency-tpool PRIVATE pthread)
target_link_libraries(concurrency-tpool PRIVATE utilities-misc)
target_link_libraries(concurrency-tpool PRIVATE utilities-try)
target_link_libraries(concurrency-tpool INTERFACE coverage_config)

if (LIBCOMMON_BUILD_TESTS)
    add_subdirectory("test")
endif ()

if(LIBCOMMON_INSTALL)
    install(TARGETS concurrency-tpool
        EXPORT concurrency-tpool-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/concurrency"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT concurrency-tpool-targets
        FILE ${PROJECT_EXPORT_NAME}-concurrency-tpool-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::concurrency::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/concurrency")
endif()
