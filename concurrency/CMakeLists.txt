add_subdirectory("rwfslock")
add_subdirectory("tpool")

add_library(concurrency INTERFACE)
target_link_libraries(concurrency INTERFACE concurrency-rwfslock)
target_link_libraries(concurrency INTERFACE concurrency-tpool)

if(LIBCOMMON_INSTALL)
    install(TARGETS concurrency concurrency-rwfslock concurrency-tpool coverage_config
        EXPORT concurrency-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(DIRECTORY
            "${CMAKE_CURRENT_SOURCE_DIR}/rwfslock/include/"
            "${CMAKE_CURRENT_SOURCE_DIR}/tpool/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBCOMMON_INCLUDEDIR}/concurrency"
        FILES_MATCHING PATTERN "*.h*")

    install(EXPORT concurrency-targets
        FILE ${LIBCOMMON_EXPORT_NAME}-concurrency-targets.cmake
        NAMESPACE ${LIBCOMMON_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
endif()
