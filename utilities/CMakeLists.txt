add_subdirectory(misc)
add_subdirectory(try)

add_library(utilities STATIC $<TARGET_OBJECTS:utilities-misc>)
target_link_libraries(utilities PUBLIC utilities-misc)
target_link_libraries(utilities INTERFACE utilities-try)
set_target_properties(utilities PROPERTIES PREFIX ${LIBCOMMON_LIBRARY_PREFIX})

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities utilities-try utilities-misc
        EXPORT utilities-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
       
    install(DIRECTORY
            "${CMAKE_CURRENT_SOURCE_DIR}/try/include/"
            "${CMAKE_CURRENT_SOURCE_DIR}/misc/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBCOMMON_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")

    install(EXPORT utilities-targets
        FILE ${LIBCOMMON_EXPORT_NAME}-utilities-targets.cmake
        NAMESPACE ${LIBCOMMON_NAMESPACE}::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${LIBCOMMON_EXPORT_NAME}")
endif()
