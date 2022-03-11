add_library(utilities-misc "src/utilities.c")

add_library(${PROJECT_NAMESPACE}::utilities::misc ALIAS utilities-misc)

target_include_directories(utilities-misc PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(utilities-misc INTERFACE coverage_config)

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities-misc
        EXPORT utilities-misc-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT utilities-misc-targets
        FILE ${PROJECT_EXPORT_NAME}-utilities-misc-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/utilities")
endif()
