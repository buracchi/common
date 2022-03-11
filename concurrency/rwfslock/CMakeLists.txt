add_library(concurrency-rwfslock
    "src/rwfslock.c")

add_library(${PROJECT_NAMESPACE}::concurrency::rwfslock ALIAS concurrency-rwfslock)

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

if(LIBCOMMON_INSTALL)
    install(TARGETS concurrency-rwfslock
        EXPORT concurrency-rwfslock-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/concurrency"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT concurrency-rwfslock-targets
        FILE ${PROJECT_EXPORT_NAME}-concurrency-rwfslock-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::concurrency::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/concurrency")
endif()
