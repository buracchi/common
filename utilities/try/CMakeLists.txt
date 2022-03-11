add_library(utilities-try INTERFACE)

add_library(${PROJECT_NAMESPACE}::utilities::try ALIAS utilities-try)

target_include_directories(utilities-try INTERFACE 
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/utilities>")

target_link_libraries(utilities-try INTERFACE coverage_config)

if(LIBCOMMON_INSTALL)
    install(TARGETS utilities-try
        EXPORT utilities-try-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utilities"
        FILES_MATCHING PATTERN "*.h*")
    
    install(EXPORT utilities-try-targets
        FILE ${PROJECT_EXPORT_NAME}-utilities-try-targets.cmake
        NAMESPACE ${PROJECT_NAMESPACE}::utilities::
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_EXPORT_NAME}/utilities")
endif()
