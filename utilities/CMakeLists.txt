add_subdirectory(misc)
add_subdirectory(try)

add_library(utilities INTERFACE)

add_library(${LIBCOMMON_NAMESPACE}::utilities ALIAS utilities)

target_compile_definitions(utilities INTERFACE UTILITIES_VERSION=1)

target_link_libraries(utilities INTERFACE utilities-misc)
target_link_libraries(utilities INTERFACE utilities-try)

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities utilities-try utilities-misc coverage_config
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
